#ifndef CGAMESCRIPTMGR_H_
#define CGAMESCRIPTMGR_H_

/*
�����Ƕ���Lua��C�ӿ���
*/

#include "LuaScriptMgr.h"

class CGameScriptMgr
{
public:
	CGameScriptMgr();
	virtual ~CGameScriptMgr();
	static void RegisterCFunction();
public:
	// ��ص�C�ӿڶ�����������
	// �ṩһ����ӡ�����־��C�ӿڹ�Lua����
	static int LogInfo(lua_State *L);
};

#endif // !CGAMESCRIPTMGR_H_