#ifndef CLUASCRIPTMGR_H_
#define CLUASCRIPTMGR_H_

#include<iostream>
#include"LuaArgsMgr.h"
#include "PersonRegisterFuncs.h"

using namespace std;

// ����lua��ص�ͷ�ļ�
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// �����࣬ȫ�ֹ���ͬһ��ʵ��
class CLuaScriptMgr
{
public:
	static CLuaScriptMgr* getInstance();
	virtual ~CLuaScriptMgr();
public:
	// ��صĲ����ӿ�
	// �������еĽŲ��ļ�
	bool LoadAllScript(const char *scriptFile);
	// ע����ص�C++������Luaʹ��
	void RegisterCFunc(const char *strFuncName, lua_CFunction func);
	// ִ��һ��Lua�ĺ���
	// û�в���
	bool ExecLuaFunction(const char *funcName);
	// �в���
	// ����1��ִ�еĺ�����
	// ����2����Ҫ�Ĳ����б�
	// ����3������ֵ�б�
	// ����4������ֵ�ĸ���
	bool ExecLuaFunction(const char *funcName, CLuaArgsMgr& luaArgs, CLuaArgsMgr* pOut = nullptr, size_t n = 0);
	// ��Lua��ջ��ѹ��ִ�еĲ���
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