#include "LuaArgsMgr.h"

CValueType::CValueType()
{
}

CValueType::~CValueType()
{
}

void CValueType::SetBool(bool bValue)
{
	_value.bValue = bValue;
	_type = C_TYPE_BOOL;
}

void CValueType::SetInt(int iValue)
{
	_value.iValue = iValue;
	_type = C_TYPE_INT;
}

void CValueType::SetLong(long lValue)
{
	_value.lValue = lValue;
	_type = C_TYPE_LONG;
}

void CValueType::SetDouble(double dValue)
{
	_value.dValue = dValue;
	_type = C_TYPE_DOUBLE;
}

void CValueType::SetString(std::string str)
{
	_value.strValue = str;	
	_type = C_TYPE_STRING;
}

CLuaArgsMgr::CLuaArgsMgr()
{
	m_LuaArgsList.clear();
}


CLuaArgsMgr::~CLuaArgsMgr()
{
	m_LuaArgsList.clear();
}

void CLuaArgsMgr::Add(bool bValue)
{
	CValueType _value_type;
	_value_type.SetBool(bValue);
	m_LuaArgsList.push_back(_value_type);
}

void CLuaArgsMgr::Add(int iValue)
{
	CValueType _value_type;
	_value_type.SetInt(iValue);
	m_LuaArgsList.push_back(_value_type);
}

void CLuaArgsMgr::Add(long lValue)
{
	CValueType _value_type;
	_value_type.SetLong(lValue);
	m_LuaArgsList.push_back(_value_type);
}

void CLuaArgsMgr::Add(double dValue)
{
	CValueType _value_type;
	_value_type.SetDouble(dValue);
	m_LuaArgsList.push_back(_value_type);
}

void CLuaArgsMgr::Add(std::string str)
{
	CValueType _value_type;
	_value_type.SetString(str);
	m_LuaArgsList.push_back(_value_type);
}

void CLuaArgsMgr::Clear()
{
	m_LuaArgsList.clear();
}

void CLuaArgsMgr::PrintDebug()
{
	for (auto iter = m_LuaArgsList.begin(); iter != m_LuaArgsList.end(); ++iter)
	{
		std::cout << "返回值类型：" << (*iter).GetType() << ",";
		switch ((*iter).GetType())
		{
		case C_TYPE_BOOL:
			std::cout << "返回值：" << (*iter).GetBool() << std::endl;
			break;
		case C_TYPE_INT:
			std::cout << "返回值：" << (*iter).GetInt() << std::endl;
			break;
		case C_TYPE_LONG:
			std::cout << "返回值：" << (*iter).GetLong() << std::endl;
			break;
		case C_TYPE_DOUBLE:
			std::cout << "返回值：" << (*iter).GetDouble() << std::endl;
			break;
		case C_TYPE_STRING:
			std::cout << "返回值：" << (*iter).GetString() << std::endl;
			break;
		}
	}
}


