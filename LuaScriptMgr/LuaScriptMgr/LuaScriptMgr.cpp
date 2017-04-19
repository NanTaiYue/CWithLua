#include "LuaScriptMgr.h"

CLuaScriptMgr* CLuaScriptMgr::m_pInstance = nullptr;

// 注册相关库
static const luaL_Reg lua_reg_libs[] = {
	{ "Person", Lua_OpenPersonLib }, //模块名字Person，注册函数Lua_OpenPersonLib
	{ NULL, NULL }
};

CLuaScriptMgr::CLuaScriptMgr()
{
	L = luaL_newstate();
	if (L == NULL)
	{
		cout << "创建Lua_State失败" << endl;
	}
	Init(L);
}

void CLuaScriptMgr::Init(lua_State * L)
{
	if (L == NULL)
	{
		cout << "初始化相关库失败" << endl;
		return;
	}
	// 初始化Lua基本的库
	//luaL_openlibs(L); // 加载所有的库
	luaopen_base(L);   // 加载基本的库
	//注册让lua使用的库
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
			cout << "加载Lua脚本失败：" << errMsg << endl;
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
		cout << "执行Lua函数，传入的函数名为空" << endl;
		return false;
	}
	int ret = lua_getglobal(L, funcName);
	if (ret != LUA_TFUNCTION) // 如果没有获取到该函数就错误
	{
		cout << "未找到该指定的函数在Lua的全局表中,函数名：" << funcName << endl;
		lua_remove(L, -1);
		return false;
	}
	int res = lua_pcall(L, 0, 0, 0);
	if (res != 0)
	{
		const char* errMsg = lua_tostring(L, 1);
		if (errMsg)
		{
			cout << "执行Lua函数失败: " << errMsg << endl;
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
		cout << "执行的Lua函数名为空" << endl;
		return false;
	}
	// 获取当前Lua堆栈的栈顶index
	int top = lua_gettop(L);
	// 获取指定函数名的函数在全局中的索引
	int ret = lua_getglobal(L, funcName);
	if (ret != LUA_TFUNCTION)
	{
		cout << "未找到该指定的函数在Lua的全局表中,函数名：" << funcName << endl;
		lua_remove(L, -1);
		return false;
	}
	// 向堆栈压入参数
	for (auto iter = luaArgs.GetLuaArgsList().begin(); iter != luaArgs.GetLuaArgsList().end(); ++iter)
	{
		PushLuaArgs(*iter);
	}
	// 是否需有返回值
	int res = lua_pcall(L, luaArgs.GetLuaArgsList().size(), n, 0);
	if (res != 0)
	{
		const char * errMsg = lua_tostring(L, 1);
		if (errMsg)
		{
			cout << "执行Lua函数失败，函数名：" << funcName << endl;
		}
		lua_pop(L, 1);
		return false;
	}
	// 如果需要有返回值，则获取返回值
	if (n != 0 && pOut)
	{
		// 获取现在栈顶的索引
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
		cout << "未定义的数据类型" << endl;
		break;
	}
}
