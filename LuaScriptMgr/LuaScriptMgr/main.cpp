#include<iostream>
using namespace std;
#include"GameScriptMgr.h"
#include"LuaScriptMgr.h"


int main()
{
	// 注册相关C接口
	CGameScriptMgr::RegisterCFunction();

	// 加载相关的lua脚本
	CLuaScriptMgr::getInstance()->LoadAllScript("test.lua");

	// 执行函数，无返回值
	CLuaScriptMgr::getInstance()->ExecLuaFunction("SayHello");

	// 调用脚本中的函数，并打印相关的数据,有一个返回值
	CLuaArgsMgr argsMgr;
	argsMgr.Add(120);
	argsMgr.Add(120);
	CLuaArgsMgr pOut;
	CLuaScriptMgr::getInstance()->ExecLuaFunction("Add", argsMgr, &pOut, 1);

	pOut.PrintDebug();

	pOut.Clear();
	argsMgr.Clear();

	// 调用函数，打印数据，有多个返回值
	argsMgr.Add(10001);
	argsMgr.Add(string("西部世界"));
	argsMgr.Add(string("xxxxx"));
	CLuaScriptMgr::getInstance()->ExecLuaFunction("TellMe", argsMgr, &pOut, 3);
	pOut.PrintDebug();

	system("pause");
	return 0;
}