#pragma once

#include <vector>
#include <iostream>
#include <assert.h>

#include "LuaAdapter/LuaAdapter.hpp"
#include "LuaAdapter/LuaFunction.hpp"
#include "LuaAdapter/LuaTable.hpp"

//ScriptingManager is tightly coupled with LuaAdapter,
//	so switching Lua libraries would take some work.

class LuaFile
{
private:
	LuaAdapter m_file;
	LuaFunction m_functions;
	LuaTable m_tables;

public:
	LuaFile()
		: m_functions(m_file)
		, m_tables(m_file)
	{}

	bool Load(const char* pData, size_t length)
	{
		return m_file.Load(pData, length);
	}

	LuaAdapter& GetLuaAdapterFile() { return m_file; }

	template <typename LuaType>
	bool Get(const char* pName, LuaType& val)
	{
		return m_file.Get(pName, val);
	}

	template <typename LuaType>
	bool Set(const char* pName, LuaType& val)
	{
		return m_file.Set(pName, val);
	}

	bool PushFunction(Lua_callback_function func, std::string name)
	{
		return m_functions.Push(func, name);
	}

	template <typename ArgsType, typename ReturnType>
	bool CallFunction(const char* functionName, const size_t argCount, const ArgsType* const args, ReturnType& returnVal)
	{
		return m_functions.Call(functionName, argCount, args, returnVal);
	}

	template <typename LuaType>
	bool TableGetSingle(const char* pTableName, const char* pVarName, LuaType& val)
	{
		if (m_tables.Open(pTableName))
		{
			bool success = m_tables.Get(pVarName, val);
			m_tables.Close();
			return success;
		}
		return false;
	}

	bool OpenTable(const char* pName)
	{
		return m_tables.Open(pName);
	}

	void CloseTable()
	{
		m_tables.Close();
		assert(m_file.GetTop() == 0);
	}

	template <typename LuaType>
	void TableGet(const char* pVarName, LuaType& val)
	{
		m_tables.Get(pVarName, val);
	}
};

class ScriptingManager
{
private:
	LuaFile m_currentFile;
	
public:
	ScriptingManager()
		: m_currentFile()
	{}

	LuaFile& GetLuaFile() { return m_currentFile; }

	bool Load(const std::string& filename);
	bool PushFunction(Lua_callback_function func, std::string name);
};
