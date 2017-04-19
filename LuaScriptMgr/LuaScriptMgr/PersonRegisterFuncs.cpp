#include "PersonRegisterFuncs.h"


int get_name(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushstring(L, (*p)->get_name().c_str());

	return 1;
}

int set_name(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TSTRING);   // ��鵱ǰջ���Ƿ�Ϊ�ַ���

	(*p)->set_name(lua_tostring(L, -1));
	return 0;
}

int get_age(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushnumber(L, (*p)->get_age());
	return 1;
}

int set_age(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TNUMBER);   // ��鵱ǰջ��

	(*p)->set_age(lua_tonumber(L, -1));
	return 0;
}

int get_sex(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushnumber(L, (*p)->get_sex());
	return 1;
}

int set_sex(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TNUMBER);   // ��鵱ǰջ��

	(*p)->set_sex(lua_tonumber(L, -1));
	return 0;
}

int get_bornDay(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushstring(L, (*p)->get_bornDay().c_str());

	return 1;
}

int set_bornDay(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TSTRING);   // ��鵱ǰջ���Ƿ�Ϊ�ַ���

	(*p)->set_bornDay(lua_tostring(L, -1));
	return 0;
}

int get_id(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	lua_pushnumber(L, (*p)->get_id());
	return 1;
}

int set_id(lua_State *L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡջ���ڴ��
	luaL_argcheck(L, p != NULL, 1, "GCPerson Invalid data");

	luaL_checktype(L, -1, LUA_TNUMBER);   // ��鵱ǰջ��

	(*p)->set_id(lua_tonumber(L, -1));
	return 0;
}

int NewPerson(lua_State * L)
{
	CPerson** p = (CPerson**)lua_newuserdata(L, sizeof(CPerson)); // ����CPerson��Ĵ�С����һ���ڴ�,����ջ��
	*p = new CPerson;
	if (*p)
	{
		luaL_getmetatable(L, PERSON); // ��ȡԪ��������ջ��
		lua_setmetatable(L, -2);   // ����Ԫ������ΪPerson��Ԫ��,��������Ԫ��
		return 1;
	}
	else
	{
		cout << "�����ڴ�ʧ��" << endl;
	}
	return 0;
}

int GCPerson(lua_State * L)
{
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡ�ڴ��
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
	CPerson** p = (CPerson**)luaL_checkudata(L, 1, PERSON); // ��ȡ�ڴ��
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

// ������ʵ�ʵĶ����йص���ط�����Ҳ����˵��Щ�������Ǹ�����������ʵ�ʶ���ʹ�õ�
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

	luaL_newmetatable(L, PERSON); // ����һ��Ԫ��������ջ��

	lua_pushvalue(L, -1);  // ����ջ����Ԫ����һ�ݣ�������ջ��

	lua_setfield(L, -2, "__index"); // ��������Ϊ-2����ֵ��������ջ�׵�Ԫ���ġ�__index��ΪԪ����������ջ����Ԫ����

	luaL_setfuncs(L, member_funcs, 0); // �����еķ���ע�뵽�ö�����
}

// ��������ķ���������Щ�����Ǵ������ÿ�ʹ�õ�
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
