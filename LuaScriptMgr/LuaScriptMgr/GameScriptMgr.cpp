#include "GameScriptMgr.h"



CGameScriptMgr::CGameScriptMgr()
{
}


CGameScriptMgr::~CGameScriptMgr()
{
}

void CGameScriptMgr::RegisterCFunction()
{
	CLuaScriptMgr::getInstance()->RegisterCFunc("LogInfo", LogInfo);
}

int CGameScriptMgr::LogInfo(lua_State * L)
{
	int args = lua_gettop(L);
	if (args != 1)
	{
		cout << "输入的参数个数错误" << endl;
		return 0;
	}
	int type = lua_type(L, 1);
	switch (type)
	{
	case LUA_TNUMBER:
		{
			int res = static_cast<int>(lua_tonumber(L, 1));
			cout << "Lua使用LogInfo函数打印的数据是：" << res << endl;
		}
		break;
	case LUA_TSTRING:
		{
			const char* str = lua_tostring(L, 1);
			cout << "Lua使用LogInfo函数打印的信息是：" << str << endl;
		}
		break;
	default:
		cout << "Lua使用LogInfo函数打印的信息是其他未知信息" << endl;
		break;
	}
	return 0;
}
