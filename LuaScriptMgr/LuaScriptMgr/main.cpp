#include<iostream>
using namespace std;
#include"GameScriptMgr.h"
#include"LuaScriptMgr.h"


int main()
{
	// ע�����C�ӿ�
	CGameScriptMgr::RegisterCFunction();

	// ������ص�lua�ű�
	CLuaScriptMgr::getInstance()->LoadAllScript("test.lua");

	// ִ�к������޷���ֵ
	CLuaScriptMgr::getInstance()->ExecLuaFunction("SayHello");

	// ���ýű��еĺ���������ӡ��ص�����,��һ������ֵ
	CLuaArgsMgr argsMgr;
	argsMgr.Add(120);
	argsMgr.Add(120);
	CLuaArgsMgr pOut;
	CLuaScriptMgr::getInstance()->ExecLuaFunction("Add", argsMgr, &pOut, 1);

	pOut.PrintDebug();

	pOut.Clear();
	argsMgr.Clear();

	// ���ú�������ӡ���ݣ��ж������ֵ
	argsMgr.Add(10001);
	argsMgr.Add(string("��������"));
	argsMgr.Add(string("xxxxx"));
	CLuaScriptMgr::getInstance()->ExecLuaFunction("TellMe", argsMgr, &pOut, 3);
	pOut.PrintDebug();

	system("pause");
	return 0;
}