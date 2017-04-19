#ifndef CLUASCRIPTMGR_H_
#define CLUASCRIPTMGR_H_

#include<iostream>
#include"LuaArgsMgr.h"
#include "PersonRegisterFuncs.h"

using namespace std;

// 包含lua相关的头文件
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// 单例类，全局共享同一个实例
class CLuaScriptMgr
{
public:
	static CLuaScriptMgr* getInstance();
	virtual ~CLuaScriptMgr();
public:
	// 相关的操作接口
	// 加载所有的脚步文件
	bool LoadAllScript(const char *scriptFile);
	// 注册相关的C++函数给Lua使用
	void RegisterCFunc(const char *strFuncName, lua_CFunction func);
	// 执行一个Lua的函数
	// 没有参数
	bool ExecLuaFunction(const char *funcName);
	// 有参数
	// 参数1：执行的函数名
	// 参数2：需要的参数列表
	// 参数3：返回值列表
	// 参数4：返回值的个数
	bool ExecLuaFunction(const char *funcName, CLuaArgsMgr& luaArgs, CLuaArgsMgr* pOut = nullptr, size_t n = 0);
	// 向Lua堆栈中压入执行的参数
	void PushLuaArgs(CValueType &value_type);
protected:
	CLuaScriptMgr();
	CLuaScriptMgr(CLuaScriptMgr &ref);
	CLuaScriptMgr operator = (CLuaScriptMgr &ref);
	void Init(lua_State *L);
private:
	static CLuaScriptMgr* m_pInstance;
	lua_State * L;
};



#endif // !CLUASCRIPTMGR_H_