/***
 cubic polynomial trajectory
 @module liba.polytraj3
*/

#include "polytraj3.h"
#include "a/polytraj3.h"

static int liba_polytraj3_gen_(lua_State *const L, a_polytraj3_s *const ctx)
{
    a_float_t t0 = 0, q0 = 0, v0 = 0;
    a_float_t t1 = 0, q1 = 0, v1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    default:
    case 6:
        v1 = (a_float_t)luaL_checknumber(L, 6);
        A_FALLTHROUGH;
    case 5:
        v0 = (a_float_t)luaL_checknumber(L, 5);
        A_FALLTHROUGH;
    case 4:
        q1 = (a_float_t)luaL_checknumber(L, 4);
        A_FALLTHROUGH;
    case 3:
        q0 = (a_float_t)luaL_checknumber(L, 3);
        A_FALLTHROUGH;
    case 2:
        t1 = (a_float_t)luaL_checknumber(L, 2);
        A_FALLTHROUGH;
    case 1:
        t0 = (a_float_t)luaL_checknumber(L, 1);
        A_FALLTHROUGH;
    case 0:;
    }
    a_polytraj3_gen(ctx, t0, t1, q0, q1, v0, v1);
    return 1;
}

/***
 constructor for cubic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj3 cubic polynomial trajectory userdata
 @function new
*/
int liba_polytraj3_new(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        a_polytraj3_s *const ctx = (a_polytraj3_s *)lua_newuserdata(L, sizeof(a_polytraj3_s));
        liba_polytraj3_meta_(L, 1);
        lua_setmetatable(L, -2);
        return liba_polytraj3_gen_(L, ctx);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_float_t source[3] = {0};
        a_float_t target[3] = {0};
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        lua_array_num_get(L, 1, source, A_LEN(source));
        lua_array_num_get(L, 2, target, A_LEN(target));
        a_polytraj3_s *const ctx = (a_polytraj3_s *)lua_newuserdata(L, sizeof(a_polytraj3_s));
        liba_polytraj3_meta_(L, 1);
        lua_setmetatable(L, -2);
        a_polytraj3_gen(ctx,
                        source[0], target[0],
                        source[1], target[1],
                        source[2], target[2]);
        return 1;
    }
    return 0;
}

/***
 generate for cubic polynomial trajectory
 @tparam a.polytraj3 ctx cubic polynomial trajectory userdata
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj3 cubic polynomial trajectory userdata
 @function gen
*/
int liba_polytraj3_gen(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 2);
    if (top > 4 && type == LUA_TNUMBER)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytraj3_s *const ctx = (a_polytraj3_s *)lua_touserdata(L, 1);
        return liba_polytraj3_gen_(L, ctx);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_float_t source[3] = {0};
        a_float_t target[3] = {0};
        luaL_checktype(L, 1, LUA_TUSERDATA);
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_polytraj3_s *const ctx = (a_polytraj3_s *)lua_touserdata(L, 1);
        lua_array_num_get(L, 2, source, A_LEN(source));
        lua_array_num_get(L, 3, target, A_LEN(target));
        a_polytraj3_gen(ctx,
                        source[0], target[0],
                        source[1], target[1],
                        source[2], target[2]);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for cubic polynomial trajectory position
 @tparam a.polytraj3 ctx cubic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_polytraj3_pos(lua_State *const L)
{
    a_polytraj3_s const *const ctx = (a_polytraj3_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj3_pos(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for cubic polynomial trajectory velocity
 @tparam a.polytraj3 ctx cubic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_polytraj3_vel(lua_State *const L)
{
    a_polytraj3_s const *const ctx = (a_polytraj3_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj3_vel(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for cubic polynomial trajectory acceleration
 @tparam a.polytraj3 ctx cubic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_polytraj3_acc(lua_State *const L)
{
    a_polytraj3_s const *const ctx = (a_polytraj3_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj3_acc(ctx, dt));
        return 1;
    }
    return 0;
}

#undef funcs
#define funcs liba_polytraj3_funcs
static lua_fun_s const funcs[] = {
    {"new", liba_polytraj3_new},
    {"gen", liba_polytraj3_gen},
    {"pos", liba_polytraj3_pos},
    {"vel", liba_polytraj3_vel},
    {"acc", liba_polytraj3_acc},
    {NULL, NULL},
};

static int liba_polytraj3_set(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0xE8859EEB: // __name
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        return 0;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
        return 0;
    }
}

static int liba_polytraj3_get(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_polytraj3_s const *const ctx = (a_polytraj3_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x00000071: // q
        lua_array_num_new(L, ctx->q, A_LEN(ctx->q));
        break;
    case 0x00000076: // v
        lua_array_num_new(L, ctx->v, A_LEN(ctx->v));
        break;
    case 0x00000061: // a
        lua_array_num_new(L, ctx->a, A_LEN(ctx->a));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, liba_polytraj3_new);
        break;
    case 0x001B2CBC: // gen
        lua_pushcfunction(L, liba_polytraj3_gen);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, liba_polytraj3_pos);
        break;
    case 0x001F1A41: // vel
        lua_pushcfunction(L, liba_polytraj3_vel);
        break;
    case 0x00199975: // acc
        lua_pushcfunction(L, liba_polytraj3_acc);
        break;
    case 0xA65758B2: // __index
    {
        lua_createtable(L, 0, A_LEN(funcs));
        lua_fun_reg(L, -1, funcs);
        lua_array_num_new(L, ctx->q, A_LEN(ctx->q));
        lua_setfield(L, -2, "q");
        lua_array_num_new(L, ctx->v, A_LEN(ctx->v));
        lua_setfield(L, -2, "v");
        lua_array_num_new(L, ctx->a, A_LEN(ctx->a));
        lua_setfield(L, -2, "a");
        break;
    }
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_polytraj3(lua_State *const L)
{
    lua_createtable(L, 0, A_LEN(funcs) - 1);
    lua_fun_reg(L, -1, funcs);
    lua_createtable(L, 0, 1);
    lua_fun_set(L, -1, "__newindex", liba_setter);
    lua_setmetatable(L, -2);

    lua_fun_s const metas[] = {
        {"__newindex", liba_polytraj3_set},
        {"__index", liba_polytraj3_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas));
    lua_str_set(L, -1, "__name", "a.polytraj3");
    lua_fun_reg(L, -1, metas);

    liba_polytraj3_meta_(L, 0);
    liba_polytraj3_func_(L, 0);

    return liba_polytraj3_func_(L, 1);
}

int liba_polytraj3_func_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_polytraj3_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_polytraj3_func_));
    return 0;
}

int liba_polytraj3_meta_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_polytraj3_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, FUNC2P(liba_polytraj3_meta_));
    return 0;
}