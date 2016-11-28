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
		cout << "����Ĳ�����������" << endl;
		return 0;
	}
	int type = lua_type(L, 1);
	switch (type)
	{
	case LUA_TNUMBER:
		{
			int res = static_cast<int>(lua_tonumber(L, 1));
			cout << "Luaʹ��LogInfo������ӡ�������ǣ�" << res << endl;
		}
		break;
	case LUA_TSTRING:
		{
			const char* str = lua_tostring(L, 1);
			cout << "Luaʹ��LogInfo������ӡ����Ϣ�ǣ�" << str << endl;
		}
		break;
	default:
		cout << "Luaʹ��LogInfo������ӡ����Ϣ������δ֪��Ϣ" << endl;
		break;
	}
	return 0;
}
