from a cimport *

cdef extern from "a/traptraj.h":
    ctypedef struct a_traptraj:
        a_float t
        a_float q0
        a_float q1
        a_float v0
        a_float v1
        a_float vc
        a_float ta
        a_float td
        a_float qa
        a_float qd
        a_float ac
        a_float de
    a_float a_traptraj_gen(a_traptraj *ctx, a_float vm, a_float ac, a_float de, a_float q0, a_float q1, a_float v0, a_float v1)
    a_float a_traptraj_pos(const a_traptraj *ctx, a_float dt)
    a_float a_traptraj_vel(const a_traptraj *ctx, a_float dt)
    a_float a_traptraj_acc(const a_traptraj *ctx, a_float dt)
