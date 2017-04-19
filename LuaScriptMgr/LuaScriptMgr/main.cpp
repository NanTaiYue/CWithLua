#include<iostream>

#include"GameScriptMgr.h"
#include"LuaScriptMgr.h"

using namespace std;

/*
关于Lua中使用C++的函数有两种方式：
1.将类定义的方法分别注册到lua_state中，在Lua中可随处调用这些函数，但是这类函数与具体的类型无关
2.将C++的类以库的形式注入Lua中，在Lua可以使用如 local obj = Message.new()的形式来创建该类的一个对象
  该对象obj可以调用一些指定的方法，这种就与具体的类型相关
  通常实现这种方式是采用元表来操作的
  
  新增注入C++类到Lua中的方式，以便在Lua中使用相关的类型来创建指定的对象
*/

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