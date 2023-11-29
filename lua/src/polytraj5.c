/***
 quintic polynomial trajectory
 @module liba.polytraj5
*/

#include "polytraj5.h"

static int liba_polytraj5_gen_(lua_State *const L, a_polytraj5_s *const ctx)
{
    a_float_t t0 = 0, q0 = 0, v0 = 0, a0 = 0;
    a_float_t t1 = 0, q1 = 0, v1 = 0, a1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 8:
        a1 = (a_float_t)luaL_checknumber(L, 8);
        A_FALLTHROUGH;
    case 7:
        a0 = (a_float_t)luaL_checknumber(L, 7);
        A_FALLTHROUGH;
    case 6:
        v1 = (a_float_t)luaL_checknumber(L, 6);
        A_FALLTHROUGH;
    case 5:
        v0 = (a_float_t)luaL_checknumber(L, 5);
        A_FALLTHROUGH;
    case 4:
        q1 = (a_float_t)luaL_checknumber(L, 4);
        q0 = (a_float_t)luaL_checknumber(L, 3);
        t1 = (a_float_t)luaL_checknumber(L, 2);
        t0 = (a_float_t)luaL_checknumber(L, 1);
        A_FALLTHROUGH;
    default:
        break;
    }
    a_polytraj5_gen(ctx, t0, t1, q0, q1, v0, v1, a0, a1);
    return 1;
}

/***
 constructor for quintic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj5 quintic polynomial trajectory userdata
 @function new
*/
int liba_polytraj5_new(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        a_polytraj5_s *const ctx = (a_polytraj5_s *)lua_newuserdata(L, sizeof(a_polytraj5_s));
        liba_polytraj5_meta_(L, 1);
        lua_setmetatable(L, -2);
        return liba_polytraj5_gen_(L, ctx);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_float_t source[4] = {0};
        a_float_t target[4] = {0};
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        l_array_num_get(L, 1, source, A_LEN(source));
        l_array_num_get(L, 2, target, A_LEN(target));
        a_polytraj5_s *const ctx = (a_polytraj5_s *)lua_newuserdata(L, sizeof(a_polytraj5_s));
        liba_polytraj5_meta_(L, 1);
        lua_setmetatable(L, -2);
        a_polytraj5_gen(ctx,
                        source[0], target[0],
                        source[1], target[1],
                        source[2], target[2],
                        source[3], target[3]);
        return 1;
    }
    return 0;
}

/***
 generate for quintic polynomial trajectory
 @tparam a.polytraj5 ctx quintic polynomial trajectory userdata
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn a.polytraj5 quintic polynomial trajectory userdata
 @function gen
*/
int liba_polytraj5_gen(lua_State *const L)
{
    int const top = lua_gettop(L);
    int const type = lua_type(L, 2);
    if (top > 4 && type == LUA_TNUMBER)
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytraj5_s *const ctx = (a_polytraj5_s *)lua_touserdata(L, 1);
        return liba_polytraj5_gen_(L, ctx);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_float_t source[4] = {0};
        a_float_t target[4] = {0};
        luaL_checktype(L, 1, LUA_TUSERDATA);
        luaL_checktype(L, 2, LUA_TTABLE);
        luaL_checktype(L, 3, LUA_TTABLE);
        a_polytraj5_s *const ctx = (a_polytraj5_s *)lua_touserdata(L, 1);
        l_array_num_get(L, 2, source, A_LEN(source));
        l_array_num_get(L, 3, target, A_LEN(target));
        a_polytraj5_gen(ctx,
                        source[0], target[0],
                        source[1], target[1],
                        source[2], target[2],
                        source[3], target[3]);
        lua_pushvalue(L, 1);
        return 1;
    }
    return 0;
}

/***
 calculate for quintic polynomial trajectory position
 @tparam a.polytraj5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number position output
 @function pos
*/
int liba_polytraj5_pos(lua_State *const L)
{
    a_polytraj5_s const *const ctx = (a_polytraj5_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj5_pos(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for quintic polynomial trajectory velocity
 @tparam a.polytraj5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number velocity output
 @function vel
*/
int liba_polytraj5_vel(lua_State *const L)
{
    a_polytraj5_s const *const ctx = (a_polytraj5_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj5_vel(ctx, dt));
        return 1;
    }
    return 0;
}

/***
 calculate for quintic polynomial trajectory acceleration
 @tparam a.polytraj5 ctx quintic polynomial trajectory userdata
 @tparam number dt difference between current time and initial time
 @treturn number acceleration output
 @function acc
*/
int liba_polytraj5_acc(lua_State *const L)
{
    a_polytraj5_s const *const ctx = (a_polytraj5_s const *)lua_touserdata(L, 1);
    if (ctx)
    {
        a_float_t const dt = (a_float_t)luaL_checknumber(L, 2);
        lua_pushnumber(L, (lua_Number)a_polytraj5_acc(ctx, dt));
        return 1;
    }
    return 0;
}

#undef funcs
#define funcs liba_polytraj5_funcs
static l_func_s const funcs[] = {
    {"new", liba_polytraj5_new},
    {"gen", liba_polytraj5_gen},
    {"pos", liba_polytraj5_pos},
    {"vel", liba_polytraj5_vel},
    {"acc", liba_polytraj5_acc},
    {NULL, NULL},
};

static int liba_polytraj5_set(lua_State *const L)
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

static int liba_polytraj5_get(lua_State *const L)
{
    char const *const field = lua_tostring(L, 2);
    a_polytraj5_s const *const ctx = (a_polytraj5_s const *)lua_touserdata(L, 1);
    a_u32_t const hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x00000071: // q
        lua_createtable(L, A_LEN(ctx->q), 0);
        l_array_num_set(L, -1, ctx->q, A_LEN(ctx->q));
        break;
    case 0x00000076: // v
        lua_createtable(L, A_LEN(ctx->v), 0);
        l_array_num_set(L, -1, ctx->v, A_LEN(ctx->v));
        break;
    case 0x00000061: // a
        lua_createtable(L, A_LEN(ctx->a), 0);
        l_array_num_set(L, -1, ctx->a, A_LEN(ctx->a));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, liba_polytraj5_new);
        break;
    case 0x001B2CBC: // gen
        lua_pushcfunction(L, liba_polytraj5_gen);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, liba_polytraj5_pos);
        break;
    case 0x001F1A41: // vel
        lua_pushcfunction(L, liba_polytraj5_vel);
        break;
    case 0x00199975: // acc
        lua_pushcfunction(L, liba_polytraj5_acc);
        break;
    case 0xA65758B2: // __index
    {
        lua_createtable(L, 0, A_LEN(funcs));
        l_func_reg(L, -1, funcs);
        lua_createtable(L, A_LEN(ctx->q), 0);
        l_array_num_set(L, -1, ctx->q, A_LEN(ctx->q));
        lua_setfield(L, -2, "q");
        lua_createtable(L, A_LEN(ctx->v), 0);
        l_array_num_set(L, -1, ctx->v, A_LEN(ctx->v));
        lua_setfield(L, -2, "v");
        lua_createtable(L, A_LEN(ctx->a), 0);
        l_array_num_set(L, -1, ctx->a, A_LEN(ctx->a));
        lua_setfield(L, -2, "a");
        break;
    }
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_polytraj5(lua_State *const L)
{
    lua_createtable(L, 0, A_LEN(funcs) - 1);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 1);
    l_func_set(L, -1, L_SET, liba_setter);
    lua_setmetatable(L, -2);

    l_func_s const metas[] = {
        {L_SET, liba_polytraj5_set},
        {L_GET, liba_polytraj5_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(metas));
    l_str_set(L, -1, L_NAME, "a.polytraj5");
    l_func_reg(L, -1, metas);

    liba_polytraj5_meta_(L, 0);
    liba_polytraj5_func_(L, 0);

    return liba_polytraj5_func_(L, 1);
}

int liba_polytraj5_func_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, L_FUNC2P(liba_polytraj5_func_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, L_FUNC2P(liba_polytraj5_func_));
    return 0;
}

int liba_polytraj5_meta_(lua_State *const L, int const ret)
{
    if (ret)
    {
        lua_rawgetp(L, LUA_REGISTRYINDEX, L_FUNC2P(liba_polytraj5_meta_));
        return 1;
    }
    lua_rawsetp(L, LUA_REGISTRYINDEX, L_FUNC2P(liba_polytraj5_meta_));
    return 0;
}
