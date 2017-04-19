#include "PersonRegisterFuncs.h"


int get_name(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushstring(L, (*p)->get_name().c_str());

	return 1;
}

int set_name(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TSTRING);   // 检查当前栈顶是否为字符串

	(*p)->set_name(lua_tostring(L, -1));
	return 0;
}

int get_age(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushnumber(L, (*p)->get_age());
	return 1;
}

int set_age(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TNUMBER);   // 检查当前栈顶

	(*p)->set_age(lua_tonumber(L, -1));
	return 0;
}

int get_sex(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushnumber(L, (*p)->get_sex());
	return 1;
}

int set_sex(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TNUMBER);   // 检查当前栈顶

	(*p)->set_sex(lua_tonumber(L, -1));
	return 0;
}

int get_bornDay(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushstring(L, (*p)->get_bornDay().c_str());

	return 1;
}

int set_bornDay(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TSTRING);   // 检查当前栈顶是否为字符串

	(*p)->set_bornDay(lua_tostring(L, -1));
	return 0;
}

int get_id(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushnumber(L, (*p)->get_id());
	return 1;
}

int set_id(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取栈底内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TNUMBER);   // 检查当前栈顶

	(*p)->set_id(lua_tonumber(L, -1));
	return 0;
}

int NewPerson(lua_State * L)
{
	CPerson** p = (CPerson**)lua_newuserdata(L, sizeof(CPerson)); // 根据CPerson类的大小创建一块内存,放在栈底
	*p = new CPerson;
	if (*p)
	{
		luaL_getmetatable(L, PERSON); // 获取元表，并放在栈顶
		lua_setmetatable(L, -2);   // 将该元表设置为Person的元表,并弹出该元表
		return 1;
	}
	else
	{
		cout << "分配内存失败" << endl;
	}
	return 0;
}

int GCPerson(lua_State * L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取内存块
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");
	if (p)
	{
		delete *p;
		*p = nullptr;
	}
	return 0;
}

int ToString(lua_State * L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // 获取内存块
	luaL_argcheck(L, p != NULL, 1, "ToString Invalid data");
	if (p)
	{
		CPerson *per = *p;
		if (per)
		{
			cout << per->get_name() << "," << per->get_age() << "," << per->get_id() << "," << per->get_sex() << "," << per->get_bornDay() << endl;
		}
	}
	return 0;
}

// 创建于实际的对象有关的相关方法，也就是说这些方法都是给创建出来的实际对象使用的
void Create_Metatable(lua_State * L)
{
	static const luaL_Reg member_funcs[] = {
		{ "get_name",get_name },
		{ "set_name",set_name },
		{ "get_age",get_age },
		{ "set_age",set_age },
		{ "get_id",get_id },
		{ "set_id",set_id },
		{ "get_sex",get_sex },
		{ "set_sex",set_sex },
		{ "get_bornDay",get_bornDay },
		{ "set_bornDay",set_bornDay },
		{ "__gc",GCPerson },
		{ "__tostring",ToString },
		{ NULL, NULL }
	};

	luaL_newmetatable(L, PERSON); // 创建一个元表，并放在栈顶

	lua_pushvalue(L, -1);  // 将该栈顶的元表复制一份，并放在栈顶

	lua_setfield(L, -2, "__index"); // 设置索引为-2处的值（即放在栈底的元表）的“__index”为元表自身，并将栈顶的元表弹出

	luaL_setfuncs(L, member_funcs, 0); // 将所有的方法注入到该对象中
}

// 创建对象的方法，即这些方法是创建给该库使用的
int Lua_OpenPersonLib(lua_State * L)
{
	Create_Metatable(L);

	static const luaL_Reg lib_funcs[] = {
		{ "New", NewPerson },
		{ NULL, NULL }
	};
	luaL_newlib(L, lib_funcs);
	return 1;
}
