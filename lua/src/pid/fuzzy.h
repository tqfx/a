/***
 fuzzy proportional integral derivative controller
 @classmod a.pid.fuzzy
*/

/***
 fuzzy proportional integral derivative controller
 @field kp proportional constant
 @field ki integral constant
 @field kd derivative constant
 @field summax maximum integral output
 @field summin minimum integral output
 @field outmax maximum final output
 @field outmin minimum final output
 @field out controller output
 @field fdb cache feedback
 @field err cache error
 @field order number of order in the square matrix
 @field joint maximum number triggered by the rule
 @table a.pid.fuzzy
*/

#ifndef L_PID_FUZZY_H
#define L_PID_FUZZY_H

#include "../pid.h"
#include "a/pid/fuzzy.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int liba_pid_fuzzy_func_(lua_State *L, int ret);
A_PUBLIC int liba_pid_fuzzy_meta_(lua_State *L, int ret);

/***
 destructor for fuzzy PID controller
 @function die
*/
A_PUBLIC int liba_pid_fuzzy_die(lua_State *L);

/***
 constructor for fuzzy PID controller
 @treturn a.pid.fuzzy fuzzy PID controller userdata
 @function new
*/
A_PUBLIC int liba_pid_fuzzy_new(lua_State *L);

/***
 initialize for fuzzy PID controller
 @treturn a.pid.fuzzy fuzzy PID controller userdata
 @function init
*/
A_PUBLIC int liba_pid_fuzzy_init(lua_State *L);

/***
 zeroing for fuzzy PID controller
 @treturn a.pid.fuzzy fuzzy PID controller userdata
 @function zero
*/
A_PUBLIC int liba_pid_fuzzy_zero(lua_State *L);

/***
 set fuzzy relational operator for fuzzy PID controller
 @tparam int op enumeration for fuzzy PID controller operator
 @treturn a.pid.fuzzy fuzzy PID controller userdata
 @function op
*/
A_PUBLIC int liba_pid_fuzzy_op(lua_State *L);

/***
 set rule base for fuzzy PID controller
 @tparam table me points to membership function parameter table, terminated by 0
 @tparam table mec points to membership function parameter table, terminated by 0
 @tparam table mkp points to Kp's rule base table which must be a square matrix
 @tparam table mki points to Ki's rule base table which must be a square matrix
 @tparam table mkd points to Kd's rule base table which must be a square matrix
 @treturn a.pid.fuzzy fuzzy PID controller userdata
 @function rule
*/
A_PUBLIC int liba_pid_fuzzy_rule(lua_State *L);

/***
 set joint buffer for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @treturn a.pid.fuzzy fuzzy PID controller userdata
 @function set_joint
*/
A_PUBLIC int liba_pid_fuzzy_joint(lua_State *L);

/***
 set proportional integral derivative constant for fuzzy PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn a.pid.fuzzy fuzzy PID controller userdata
 @function kpid
*/
A_PUBLIC int liba_pid_fuzzy_kpid(lua_State *L);

/***
 calculate for fuzzy PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number setpoint value
 @function off
*/
A_PUBLIC int liba_pid_fuzzy_off(lua_State *L);

/***
 calculate for positional fuzzy PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function pos
*/
A_PUBLIC int liba_pid_fuzzy_pos(lua_State *L);

/***
 calculate for incremental fuzzy PID controller
 @tparam number set setpoint value
 @tparam number fdb feedback value
 @treturn number output value
 @function inc
*/
A_PUBLIC int liba_pid_fuzzy_inc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* pid/fuzzy.h */
