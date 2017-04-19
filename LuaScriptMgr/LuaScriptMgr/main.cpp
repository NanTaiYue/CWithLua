#include<iostream>

#include"GameScriptMgr.h"
#include"LuaScriptMgr.h"

using namespace std;

/*
����Lua��ʹ��C++�ĺ��������ַ�ʽ��
1.���ඨ��ķ����ֱ�ע�ᵽlua_state�У���Lua�п��洦������Щ�������������ຯ�������������޹�
2.��C++�����Կ����ʽע��Lua�У���Lua����ʹ���� local obj = Message.new()����ʽ�����������һ������
  �ö���obj���Ե���һЩָ���ķ��������־��������������
  ͨ��ʵ�����ַ�ʽ�ǲ���Ԫ����������
  
  ����ע��C++�ൽLua�еķ�ʽ���Ա���Lua��ʹ����ص�����������ָ���Ķ���
*/

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