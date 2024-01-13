#include "a/pid.h"

void a_pid_zero(a_pid *const ctx)
{
    ctx->sum = 0;
    ctx->out = 0;
    ctx->fdb = 0;
    ctx->var = 0;
    ctx->err = 0;
}

void a_pid_init(a_pid *const ctx) { a_pid_zero(ctx); }

void a_pid_kpid(a_pid *const ctx, a_float const kp, a_float const ki, a_float const kd)
{
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

A_HIDDEN a_float a_pid_run_(a_pid *ctx, a_float set, a_float fdb, a_float err);
a_float a_pid_run(a_pid *const ctx, a_float const set, a_float const fdb)
{
    return a_pid_run_(ctx, set, fdb, set - fdb);
}
a_float a_pid_run_(a_pid *const ctx, a_float const set, a_float const fdb, a_float const err)
{
    a_float const var = ctx->fdb - fdb;
    ctx->out = A_SAT(set, ctx->outmin, ctx->outmax);
    ctx->fdb = fdb;
    ctx->var = var;
    ctx->err = err;
    return ctx->out;
}

A_HIDDEN a_float a_pid_pos_(a_pid *ctx, a_float fdb, a_float err);
a_float a_pid_pos(a_pid *const ctx, a_float const set, a_float const fdb)
{
    return a_pid_pos_(ctx, fdb, set - fdb);
}
a_float a_pid_pos_(a_pid *const ctx, a_float const fdb, a_float const err)
{
    a_float const var = ctx->fdb - fdb;
    // When the limit of integration is exceeded or the direction of integration is the same, the integration stops.
    if ((ctx->sum > ctx->summin && ctx->sum < ctx->summax) || ctx->sum * err < 0)
    {
#if 1
        ctx->sum += ctx->ki * err; // sum = K_i[\sum^k_{i=0}err(i)]
#else
        ctx->sum += ctx->ki * (err + ctx->err) * A_FLOAT_C(0.5);
#endif
    }
    // Avoid derivative kick, fdb[k-1]-fdb[k]. out = K_p[err(k)]+sum+K_d[fdb(k-1)-fdb(k)].
    ctx->out = ctx->kp * err + ctx->sum + ctx->kd * var;
    ctx->out = A_SAT(ctx->out, ctx->outmin, ctx->outmax);
    ctx->fdb = fdb;
    ctx->var = var;
    ctx->err = err;
    return ctx->out;
}

A_HIDDEN a_float a_pid_inc_(a_pid *ctx, a_float fdb, a_float err);
a_float a_pid_inc(a_pid *const ctx, a_float const set, a_float const fdb)
{
    return a_pid_inc_(ctx, fdb, set - fdb);
}
a_float a_pid_inc_(a_pid *const ctx, a_float const fdb, a_float const err)
{
    a_float const var = ctx->fdb - fdb;
    ctx->out += ctx->kp * (err - ctx->err) + ctx->ki * err + ctx->kd * (var - ctx->var);
    ctx->out = A_SAT(ctx->out, ctx->outmin, ctx->outmax);
    ctx->fdb = fdb;
    ctx->var = var;
    ctx->err = err;
    return ctx->out;
}
