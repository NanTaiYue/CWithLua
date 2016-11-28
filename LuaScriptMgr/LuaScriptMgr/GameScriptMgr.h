#ifndef CGAMESCRIPTMGR_H_
#define CGAMESCRIPTMGR_H_

/*
该类是定义Lua的C接口类
*/

#include "LuaScriptMgr.h"

class CGameScriptMgr
{
public:
	CGameScriptMgr();
	virtual ~CGameScriptMgr();
	static void RegisterCFunction();
public:
	// 相关的C接口都定义在这里
	// 提供一个打印相关日志的C接口供Lua调用
	static int LogInfo(lua_State *L);
};

#endif // !CGAMESCRIPTMGR_H_