#ifndef C_PERSON_REGISTER_FUNCS_H_
#define C_PERSON_REGISTER_FUNCS_H_

/*
定义一个注册到Lua中的类相关的操作
*/
// 包含lua相关的头文件
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include"Person.h"

#define PERSON "Person"

static int get_name(lua_State *L);
static int set_name(lua_State *L);

static int get_age(lua_State *L);
static int  set_age(lua_State *L);

static int get_sex(lua_State *L);
static int  set_sex(lua_State *L);

static int get_bornDay(lua_State *L);
static int   set_bornDay(lua_State *L);

static int  get_id(lua_State *L);
static int  set_id(lua_State *L);

static int NewPerson(lua_State *L);

static int GCPerson(lua_State *L);

static int ToString(lua_State *L);

static void Create_Metatable(lua_State *L);

int Lua_OpenPersonLib(lua_State *L);

#endif // !C_PERSON_REGISTER_FUNCS_H_
