#include "SFMLSystem.h"

#include <iostream>
#include <fstream>

#include "AirEngine.h"
#include "SFML/System.hpp"
#include "Logger.h"

#include "zlib/zlib.h"

// Define MAX_PATH here if it hasn't been defined already to keep from having to include any OS files.
// NOTE: This was snagged from WinDef.h
#ifndef MAX_PATH
    #define MAX_PATH 260
#endif

bool SFMLSystem::LoadFileFromZip(const char* pZipFilename, FileData& fileData)
{
    //Try to open the zip file
    std::fstream zipFile;
    zipFile.open(pZipFilename, std::ios::in | std::ios::binary);
    
    if (!zipFile.is_open())
    {
        LOG("Unable to load zip: " << pZipFilename);
        return false;
    }

    //Create a header object and zero it out
    ZipDirHeader dirHeader;
    memset(&dirHeader, 0, sizeof(ZipDirHeader));

    //Seek to the header and read it into our header object
    zipFile.seekg(kPtrDelta, std::ios::end);
    const auto dirHeaderOffset = zipFile.tellg();

    zipFile.read(reinterpret_cast<char*>(&dirHeader), sizeof(ZipDirHeader));
    if (dirHeader.sig != ZipDirHeader::kSignature)
    {
        LOG("Corrupt zip: " << pZipFilename);
        return false;
    }

    //Seek to the file entries
    zipFile.seekg(static_cast<ptrdiff_t>(dirHeaderOffset) - dirHeader.dirSize, std::ios::beg);

    //Read the file entries
    const size_t allocSize = dirHeader.dirSize + dirHeader.nDirEntries * sizeof(ZipDirFileHeader*);
    char* pFileHeaders = BLEACH_NEW_ARRAY(char, allocSize);
    char* pFileHeadersPtr = pFileHeaders;
    memset(pFileHeaders, 0, allocSize);
    zipFile.read(pFileHeaders, dirHeader.dirSize);

    for (int i = 0; i < dirHeader.nDirEntries; ++i)
    {
        ZipDirFileHeader& fileHeader = *reinterpret_cast<ZipDirFileHeader*>(pFileHeaders);

        if (fileHeader.sig == ZipDirFileHeader::kSignature)
        {
            pFileHeaders += sizeof(fileHeader);

#ifdef _WIN32
            //Convert forward slashes to backlashes (Windows only)
            for (int j = 0; j < fileHeader.fnameLen; j++)
            {
                if (pFileHeaders[j] == '/')
                    pFileHeaders[j] = '\\';  
            }
#endif

            char fileName[MAX_PATH];
            memcpy(fileName, pFileHeaders, fileHeader.fnameLen);
           
           //Add terminating zero so it can be used as a string
            fileName[fileHeader.fnameLen] = '\0';

            //We found a matching file
            if (fileData.filepath == fileName)
            {
                //Try to load the file
                if (LoadBytesFromZipFile(zipFile, fileData, fileHeader))
                {
                    BLEACH_DELETE_ARRAY(pFileHeadersPtr);
                    return true;
                }
                
                //We failed to load the file
                BLEACH_DELETE_ARRAY(pFileHeadersPtr);
                return false;
            }
        }
        else
        {
            ERR("Invalid File Found in Zip");
        }

        // Skip name, extra and comment fields.
        pFileHeaders += fileHeader.fnameLen + fileHeader.xtraLen + fileHeader.cmntLen;
    }

    LOG("File not found in Zip: " << fileData.filepath);
    BLEACH_DELETE_ARRAY(pFileHeadersPtr);
    return false;
}

const char* SFMLSystem::GetSystemName() const
{
// For the purposes of this engine, these are
//  just an example. Since SFML can handle most
//  of these out of the box, we /could/ build for
//  these, but we won't.
#ifdef _WIN32
    return "Windows";
#elif defined(__APPLE__) || defined(__MACH__)
    return "Apple";
#elif defined(__linux__)
    return "Linux";
#elif defined(__android__)
    return "Android";
#elif defined(__unix__) || defined(unix) || defined(unix)
    return "Unix";
#else
    return "Undefined OS";
#endif
}

// Load raw chars from file
bool SFMLSystem::LoadRaw(FileData& fileData)
{
    sf::FileInputStream fileStream;
    fileStream.open(fileData.filepath);
    
    fileData.size = fileStream.getSize();
    if (fileData.size == -1) // Error
    {
        ERR("Error reading File: " << fileData.filepath);
        return false;
    }

    fileData.pData = BLEACH_NEW_ARRAY(char, fileData.size);
    fileStream.read(fileData.pData, fileData.size);
    return true;
}

double SFMLSystem::GetElapsedTime()
{
    float time = m_timer.getElapsedTime().asSeconds();
    m_timer.restart();
    return static_cast<double>(time);
}

// Load raw chars from ZIP file
bool SFMLSystem::LoadBytesFromZipFile(std::fstream& zipFile, FileData& fileData, ZipDirFileHeader& fileHeader)
{
    //Read the local header
    ZipLocalHeader localHeader;
    memset(&localHeader, 0, sizeof(localHeader));

    zipFile.seekg(fileHeader.hdrOffset, std::ios::beg);
    zipFile.read(reinterpret_cast<char*>(&localHeader), sizeof(ZipLocalHeader));
    if (localHeader.sig != ZipLocalHeader::kSignature)
    {
        ERR("Corrupted local header\n");
        return false;
    }

    // Skip extra fields
    zipFile.seekg(localHeader.fnameLen + localHeader.xtraLen, std::ios::cur);

    switch (localHeader.compression)
    {
        case Z_NO_COMPRESSION:
        {
            fileData.size = localHeader.ucSize;
            fileData.pData = BLEACH_NEW_ARRAY(char, fileData.size);
            zipFile.read(fileData.pData, fileData.size);
            break;
        }
        case Z_DEFLATED:
        {
            // Alloc compressed data buffer and read the whole stream
            fileData.size = localHeader.ucSize;
            fileData.pData = BLEACH_NEW_ARRAY(char, fileData.size);
            zipFile.read(fileData.pData, localHeader.cSize);

            // Setup the inflate stream.
            z_stream stream;

            char* pData = BLEACH_NEW_ARRAY(char, fileData.size);
            stream.next_in = (Bytef*)fileData.pData;
            stream.avail_in = (uInt)localHeader.cSize;
            stream.next_out = (Bytef*)pData;
            stream.avail_out = localHeader.ucSize;
            stream.zalloc = (alloc_func)0;
            stream.zfree = (free_func)0;

            // Perform inflation. wbits < 0 indicates no zlib header inside the data.
            int err = inflateInit2(&stream, -MAX_WBITS);
            if (err == Z_OK)
            {
                err = inflate(&stream, Z_FINISH);
                inflateEnd(&stream);
                if (err == Z_STREAM_END)
                    err = Z_OK;
                inflateEnd(&stream);
            }
            else
            {
                ERR("Unable to inflate Zip File");
            }

            BLEACH_DELETE_ARRAY(pData);
            break;
        }
        default:
        {
            ERR("File found with unknown compression: " << fileData.filepath);
            break;
        }
    }
    return true;
}
