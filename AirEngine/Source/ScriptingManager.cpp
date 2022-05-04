#include "ScriptingManager.h"

#include "AirEngine.h"
#include "RawBytes.h"

bool ScriptingManager::Load(const std::string& filename)
{
	RawBytes* pBytes = static_cast<RawBytes*>(AirEngine::GetResourceManager()->Load(filename.c_str()));
	return m_currentFile.Load((char*)pBytes->GetBytes(), pBytes->GetSize());
}

bool ScriptingManager::PushFunction(Lua_callback_function func, std::string name)
{
	return m_currentFile.PushFunction(func, name);
}