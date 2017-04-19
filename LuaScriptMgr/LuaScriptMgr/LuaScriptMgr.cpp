#include "LuaScriptMgr.h"

CLuaScriptMgr* CLuaScriptMgr::m_pInstance = nullptr;

// ע����ؿ�
static const luaL_Reg lua_reg_libs[] = {
	{ "Person", Lua_OpenPersonLib }, //ģ������Person��ע�ắ��Lua_OpenPersonLib
	{ NULL, NULL }
};

CLuaScriptMgr::CLuaScriptMgr()
{
	L = luaL_newstate();
	if (L == NULL)
	{
		cout << "����Lua_Stateʧ��" << endl;
	}
	Init(L);
}

void CLuaScriptMgr::Init(lua_State * L)
{
	if (L == NULL)
	{
		cout << "��ʼ����ؿ�ʧ��" << endl;
		return;
	}
	// ��ʼ��Lua�����Ŀ�
	//luaL_openlibs(L); // �������еĿ�
	luaopen_base(L);   // ���ػ����Ŀ�
	//ע����luaʹ�õĿ�
	const luaL_Reg* lua_reg = lua_reg_libs;
	for (; lua_reg->func; ++lua_reg) {
		luaL_requiref(L, lua_reg->name, lua_reg->func, 1);
		lua_pop(L, 1);
	}
}


CLuaScriptMgr * CLuaScriptMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CLuaScriptMgr;
	}
	return m_pInstance;
}

CLuaScriptMgr::~CLuaScriptMgr()
{
	if (m_pInstance)
	{
		lua_close(L);
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

bool CLuaScriptMgr::LoadAllScript(const char * scriptFile)
{
	if (scriptFile == nullptr)
	{
		cout << "scriptFile is nullptr" << endl;
		return false;
	}
	int ret = luaL_dofile(L, scriptFile);
	if (ret != 0)
	{
		const char* errMsg = lua_tostring(L, 1);
		if (errMsg)
		{
			cout << "����Lua�ű�ʧ�ܣ�" << errMsg << endl;
		}
		return false;
	}
	return false;
}

void CLuaScriptMgr::RegisterCFunc(const char *strFuncName, lua_CFunction func)
{
	if (strFuncName != nullptr)
	{
		lua_register(L, strFuncName, func);
	}
}

bool CLuaScriptMgr::ExecLuaFunction(const char * funcName)
{
	if (funcName == nullptr)
	{
		cout << "ִ��Lua����������ĺ�����Ϊ��" << endl;
		return false;
	}
	int ret = lua_getglobal(L, funcName);
	if (ret != LUA_TFUNCTION) // ���û�л�ȡ���ú����ʹ���
	{
		cout << "δ�ҵ���ָ���ĺ�����Lua��ȫ�ֱ���,��������" << funcName << endl;
		lua_remove(L, -1);
		return false;
	}
	int res = lua_pcall(L, 0, 0, 0);
	if (res != 0)
	{
		const char* errMsg = lua_tostring(L, 1);
		if (errMsg)
		{
			cout << "ִ��Lua����ʧ��: " << errMsg << endl;
		}
		lua_pop(L, 1);
		return false;
	}
	return true;
}

bool CLuaScriptMgr::ExecLuaFunction(const char * funcName, CLuaArgsMgr & luaArgs, CLuaArgsMgr * pOut, size_t n)
{
	if (funcName == nullptr)
	{
		cout << "ִ�е�Lua������Ϊ��" << endl;
		return false;
	}
	// ��ȡ��ǰLua��ջ��ջ��index
	int top = lua_gettop(L);
	// ��ȡָ���������ĺ�����ȫ���е�����
	int ret = lua_getglobal(L, funcName);
	if (ret != LUA_TFUNCTION)
	{
		cout << "δ�ҵ���ָ���ĺ�����Lua��ȫ�ֱ���,��������" << funcName << endl;
		lua_remove(L, -1);
		return false;
	}
	// ���ջѹ�����
	for (auto iter = luaArgs.GetLuaArgsList().begin(); iter != luaArgs.GetLuaArgsList().end(); ++iter)
	{
		PushLuaArgs(*iter);
	}
	// �Ƿ����з���ֵ
	int res = lua_pcall(L, luaArgs.GetLuaArgsList().size(), n, 0);
	if (res != 0)
	{
		const char * errMsg = lua_tostring(L, 1);
		if (errMsg)
		{
			cout << "ִ��Lua����ʧ�ܣ���������" << funcName << endl;
		}
		lua_pop(L, 1);
		return false;
	}
	// �����Ҫ�з���ֵ�����ȡ����ֵ
	if (n != 0 && pOut)
	{
		// ��ȡ����ջ��������
		int nowTop = lua_gettop(L);
		for (int i = top+1; i <= nowTop; ++i)
		{
			int type = lua_type(L, i);
			switch (type)
			{
			case LUA_TBOOLEAN:
				{
					int r = lua_toboolean(L, i);
					pOut->Add(r == 0? false : true);
				}
				break;
			case LUA_TNUMBER:
				{
					int num = static_cast<int>(lua_tonumber(L, i));
					pOut->Add(num);
				}
				break;
			case LUA_TSTRING:
				{
					const char* str = lua_tostring(L, i);
					pOut->Add(string(str));
				}
				break;
			default:
				break;
			}
		}
		lua_pop(L, nowTop - top);
	}
	return true;
}

void CLuaScriptMgr::PushLuaArgs(CValueType & value_type)
{
	C_TYPE _type = value_type.GetType();
	switch (_type)
	{
	case C_TYPE_BOOL:
		lua_pushboolean(L, value_type.GetBool());
		break;
	case C_TYPE_INT:
		lua_pushinteger(L, (lua_Integer)value_type.GetInt());
		break;
	case C_TYPE_LONG:
		lua_pushinteger(L, (lua_Integer)value_type.GetLong());
		break;
	case C_TYPE_DOUBLE:
		lua_pushnumber(L, (lua_Number)value_type.GetDouble());
		break;
	case C_TYPE_STRING:
		lua_pushstring(L, value_type.GetString().c_str());
		break;
	case C_TYPE_ALL:
	default:
		cout << "δ�������������" << endl;
		break;
	}
}
