/***
 membership function
 @module liba.mf
*/

#include "a.h"
#include "a/mf.h"

/***
 gaussian membership function
 @tparam number x input value for which to compute membership value.
 @tparam number sigma is the standard deviation.
 @tparam number c is the mean.
 @treturn number membership value.
 @function gauss
*/
static int LMODULE(mf_gauss_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const sigma = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const c = (a_float_t)luaL_checknumber(L, Li + 2);
    lua_pushnumber(L, (lua_Number)a_mf_gauss(x, sigma, c));
    return 1;
}
static int LMODULE(mf_gauss)(lua_State *const L)
{
    return LMODULE(mf_gauss_)(L, 1);
}

/***
 product of two sigmoidal membership functions
 @tparam number x input value for which to compute membership value.
 @tparam number sigma1 is the standard deviation of the left gaussian function.
 @tparam number c1 is the mean of the left gaussian function.
 @tparam number sigma2 is the standard deviation of the right gaussian function.
 @tparam number c2 is the mean of the right gaussian function.
 @treturn number membership value.
 @function gauss2
*/
static int LMODULE(mf_gauss2_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const sigma1 = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const c1 = (a_float_t)luaL_checknumber(L, Li + 2);
    a_float_t const sigma2 = (a_float_t)luaL_checknumber(L, Li + 3);
    a_float_t const c2 = (a_float_t)luaL_checknumber(L, Li + 4);
    lua_pushnumber(L, (lua_Number)a_mf_gauss2(x, sigma1, c1, sigma2, c2));
    return 1;
}
static int LMODULE(mf_gauss2)(lua_State *const L)
{
    return LMODULE(mf_gauss2_)(L, 1);
}

/***
 generalized bell-shaped membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines the width of the membership function, where a larger value creates a wider membership function.
 @tparam number b defines the shape of the curve on either side of the central plateau, where a larger value creates a more steep transition.
 @tparam number c defines the center of the membership function.
 @treturn number membership value.
 @function gbell
*/
static int LMODULE(mf_gbell_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const b = (a_float_t)luaL_checknumber(L, Li + 2);
    a_float_t const c = (a_float_t)luaL_checknumber(L, Li + 3);
    lua_pushnumber(L, (lua_Number)a_mf_gbell(x, a, b, c));
    return 1;
}
static int LMODULE(mf_gbell)(lua_State *const L)
{
    return LMODULE(mf_gbell_)(L, 1);
}

/***
 sigmoidal membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines the width of the transition area.
 @tparam number c defines the center of the transition area.
 @treturn number membership value.
 @function sig
*/
static int LMODULE(mf_sig_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const c = (a_float_t)luaL_checknumber(L, Li + 2);
    lua_pushnumber(L, (lua_Number)a_mf_sig(x, a, c));
    return 1;
}
static int LMODULE(mf_sig)(lua_State *const L)
{
    return LMODULE(mf_sig_)(L, 1);
}

/***
 difference between two sigmoidal membership functions
 @tparam number x input value for which to compute membership value.
 @tparam number a1 defines the width of the first transition area.
 @tparam number c1 defines the center of the first transition area.
 @tparam number a2 defines the width of the second transition area.
 @tparam number c2 defines the center of the second transition area.
 @treturn number membership value.
 @function dsig
*/
static int LMODULE(mf_dsig_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a1 = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const c1 = (a_float_t)luaL_checknumber(L, Li + 2);
    a_float_t const a2 = (a_float_t)luaL_checknumber(L, Li + 3);
    a_float_t const c2 = (a_float_t)luaL_checknumber(L, Li + 4);
    lua_pushnumber(L, (lua_Number)a_mf_dsig(x, a1, c1, a2, c2));
    return 1;
}
static int LMODULE(mf_dsig)(lua_State *const L)
{
    return LMODULE(mf_dsig_)(L, 1);
}

/***
 product of two sigmoidal membership functions
 @tparam number x input value for which to compute membership value.
 @tparam number a1 defines the width of the first transition area.
 @tparam number c1 defines the center of the first transition area.
 @tparam number a2 defines the width of the second transition area.
 @tparam number c2 defines the center of the second transition area.
 @treturn number membership value.
 @function psig
*/
static int LMODULE(mf_psig_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a1 = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const c1 = (a_float_t)luaL_checknumber(L, Li + 2);
    a_float_t const a2 = (a_float_t)luaL_checknumber(L, Li + 3);
    a_float_t const c2 = (a_float_t)luaL_checknumber(L, Li + 4);
    lua_pushnumber(L, (lua_Number)a_mf_psig(x, a1, c1, a2, c2));
    return 1;
}
static int LMODULE(mf_psig)(lua_State *const L)
{
    return LMODULE(mf_psig_)(L, 1);
}

/***
 trapezoidal membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its left foot.
 @tparam number b defines its left shoulder.
 @tparam number c defines its right shoulder.
 @tparam number d defines its right foot.
 @treturn number membership value.
 @function trap
*/
static int LMODULE(mf_trap_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const b = (a_float_t)luaL_checknumber(L, Li + 2);
    a_float_t const c = (a_float_t)luaL_checknumber(L, Li + 3);
    a_float_t const d = (a_float_t)luaL_checknumber(L, Li + 4);
    lua_pushnumber(L, (lua_Number)a_mf_trap(x, a, b, c, d));
    return 1;
}
static int LMODULE(mf_trap)(lua_State *const L)
{
    return LMODULE(mf_trap_)(L, 1);
}

/***
 triangular membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its left foot.
 @tparam number b defines its peak.
 @tparam number c defines its right foot.
 @treturn number membership value.
 @function tri
*/
static int LMODULE(mf_tri_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const b = (a_float_t)luaL_checknumber(L, Li + 2);
    a_float_t const c = (a_float_t)luaL_checknumber(L, Li + 3);
    lua_pushnumber(L, (lua_Number)a_mf_tri(x, a, b, c));
    return 1;
}
static int LMODULE(mf_tri)(lua_State *const L)
{
    return LMODULE(mf_tri_)(L, 1);
}

/***
 linear s-shaped saturation membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its foot.
 @tparam number b defines its shoulder.
 @treturn number membership value.
 @function lins
*/
static int LMODULE(mf_lins_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const b = (a_float_t)luaL_checknumber(L, Li + 2);
    lua_pushnumber(L, (lua_Number)a_mf_lins(x, a, b));
    return 1;
}
static int LMODULE(mf_lins)(lua_State *const L)
{
    return LMODULE(mf_lins_)(L, 1);
}

/***
 linear z-shaped saturation membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its shoulder.
 @tparam number b defines its foot.
 @treturn number membership value.
 @function linz
*/
static int LMODULE(mf_linz_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const b = (a_float_t)luaL_checknumber(L, Li + 2);
    lua_pushnumber(L, (lua_Number)a_mf_linz(x, a, b));
    return 1;
}
static int LMODULE(mf_linz)(lua_State *const L)
{
    return LMODULE(mf_linz_)(L, 1);
}

/***
 s-shaped membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its foot.
 @tparam number b defines its shoulder.
 @treturn number membership value.
 @function s
*/
static int LMODULE(mf_s_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const b = (a_float_t)luaL_checknumber(L, Li + 2);
    lua_pushnumber(L, (lua_Number)a_mf_s(x, a, b));
    return 1;
}
static int LMODULE(mf_s)(lua_State *const L)
{
    return LMODULE(mf_s_)(L, 1);
}

/***
 z-shaped membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its shoulder.
 @tparam number b defines its foot.
 @treturn number membership value.
 @function z
*/
static int LMODULE(mf_z_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const b = (a_float_t)luaL_checknumber(L, Li + 2);
    lua_pushnumber(L, (lua_Number)a_mf_z(x, a, b));
    return 1;
}
static int LMODULE(mf_z)(lua_State *const L)
{
    return LMODULE(mf_z_)(L, 1);
}

/***
 z-shaped membership function
 @tparam number x input value for which to compute membership value.
 @tparam number a defines its left foot.
 @tparam number b defines its left shoulder.
 @tparam number c defines its right shoulder.
 @tparam number d defines its right foot.
 @treturn number membership value.
 @function pi
*/
static int LMODULE(mf_pi_)(lua_State *const L, int const Li)
{
    a_float_t const x = (a_float_t)luaL_checknumber(L, Li + 0);
    a_float_t const a = (a_float_t)luaL_checknumber(L, Li + 1);
    a_float_t const b = (a_float_t)luaL_checknumber(L, Li + 2);
    a_float_t const c = (a_float_t)luaL_checknumber(L, Li + 3);
    a_float_t const d = (a_float_t)luaL_checknumber(L, Li + 4);
    lua_pushnumber(L, (lua_Number)a_mf_pi(x, a, b, c, d));
    return 1;
}
static int LMODULE(mf_pi)(lua_State *const L)
{
    return LMODULE(mf_pi_)(L, 1);
}

/***
 membership function
 @tparam int e type for membership function
 @tparam number x input value for which to compute membership value.
 @tparam number ... is an array that stores parameters.
 @treturn number membership value.
 @function mf
*/
static int LMODULE(mf_mf)(lua_State *const L)
{
    int Li = 1;
    lua_Integer const e = luaL_checkinteger(L, Li++);
    switch (e)
    {
    case A_MF_PI:
        return LMODULE(mf_pi_)(L, Li);
    case A_MF_Z:
        return LMODULE(mf_z_)(L, Li);
    case A_MF_S:
        return LMODULE(mf_s_)(L, Li);
    case A_MF_LINZ:
        return LMODULE(mf_linz_)(L, Li);
    case A_MF_LINS:
        return LMODULE(mf_lins_)(L, Li);
    case A_MF_TRI:
        return LMODULE(mf_tri_)(L, Li);
    case A_MF_TRAP:
        return LMODULE(mf_trap_)(L, Li);
    case A_MF_PSIG:
        return LMODULE(mf_psig_)(L, Li);
    case A_MF_DSIG:
        return LMODULE(mf_dsig_)(L, Li);
    case A_MF_SIG:
        return LMODULE(mf_sig_)(L, Li);
    case A_MF_GBELL:
        return LMODULE(mf_gbell_)(L, Li);
    case A_MF_GAUSS2:
        return LMODULE(mf_gauss2_)(L, Li);
    case A_MF_GAUSS:
        return LMODULE(mf_gauss_)(L, Li);
    case A_MF_NUL:
    default:
        return 0;
    }
}

int LMODULE_(mf, lua_State *const L)
{
    /***
     enumeration for membership function
     @field NUL none
     @field GAUSS gaussian membership function
     @field GAUSS2 gaussian combination membership function
     @field GBELL generalized bell-shaped membership function
     @field SIG sigmoidal membership function
     @field DSIG difference between two sigmoidal membership functions
     @field PSIG product of two sigmoidal membership functions
     @field TRAP trapezoidal membership function
     @field TRI triangular membership function
     @field LINS linear s-shaped saturation membership function
     @field LINZ linear z-shaped saturation membership function
     @field S s-shaped membership function
     @field Z z-shaped membership function
     @field PI pi-shaped membership function
     @table mf
    */
    l_int_s const enums[] = {
        {"NUL", A_MF_NUL},
        {"GAUSS", A_MF_GAUSS},
        {"GAUSS2", A_MF_GAUSS2},
        {"GBELL", A_MF_GBELL},
        {"SIG", A_MF_SIG},
        {"DSIG", A_MF_DSIG},
        {"PSIG", A_MF_PSIG},
        {"TRAP", A_MF_TRAP},
        {"TRI", A_MF_TRI},
        {"LINS", A_MF_LINS},
        {"LINZ", A_MF_LINZ},
        {"S", A_MF_S},
        {"Z", A_MF_Z},
        {"PI", A_MF_PI},
        {NULL, 0},
    };
    l_func_s const funcs[] = {
        {"gauss", LMODULE(mf_gauss)},
        {"gauss2", LMODULE(mf_gauss2)},
        {"gbell", LMODULE(mf_gbell)},
        {"sig", LMODULE(mf_sig)},
        {"dsig", LMODULE(mf_dsig)},
        {"psig", LMODULE(mf_psig)},
        {"trap", LMODULE(mf_trap)},
        {"tri", LMODULE(mf_tri)},
        {"lins", LMODULE(mf_lins)},
        {"linz", LMODULE(mf_linz)},
        {"s", LMODULE(mf_s)},
        {"z", LMODULE(mf_z)},
        {"pi", LMODULE(mf_pi)},
        {"mf", LMODULE(mf_mf)},
        {NULL, NULL},
    };
    lua_createtable(L, 0, A_LEN(enums) + A_LEN(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 1);
    l_func_set(L, -1, L_SET, LMODULE(setter));
    lua_setmetatable(L, -2);
    return 1;
}
