#define LIBA_PID_C
#include "pid.h"

void a_pid_set_dt(a_pid_s *const ctx, a_float_t const dt)
{
    a_float_t const t = dt / ctx->dt;
    ctx->ki *= t;
    ctx->kd /= t;
    ctx->dt = dt;
}

a_pid_s *a_pid_off(a_pid_s *const ctx)
{
    a_pid_set_mode(ctx, A_PID_OFF);
    return ctx;
}

a_pid_s *a_pid_inc(a_pid_s *const ctx)
{
    a_pid_set_mode(ctx, A_PID_INC);
    return ctx;
}

a_pid_s *a_pid_pos(a_pid_s *const ctx, a_float_t const max)
{
    ctx->summax = A_ABS(max);
    if (ctx->summax > ctx->outmax)
    {
        ctx->summax = ctx->outmax;
    }
    a_pid_set_mode(ctx, A_PID_POS);
    return ctx;
}

a_pid_s *a_pid_kpid(a_pid_s *const ctx, a_float_t const kp, a_float_t const ki, a_float_t const kd)
{
    ctx->kp = kp;
    ctx->ki = ki * ctx->dt;
    ctx->kd = kd / ctx->dt;
    return ctx;
}

void a_pid_chan_(a_pid_s *const ctx, a_float_t *const out, a_float_t *const fdb, a_float_t *const tmp, a_float_t *const err)
{
    ctx->out.p = out;
    ctx->fdb.p = fdb;
    ctx->tmp.p = tmp;
    ctx->err.p = err;
}

a_pid_s *a_pid_chan(a_pid_s *const ctx, unsigned int const num, a_float_t *const out, a_float_t *const fdb, a_float_t *const tmp, a_float_t *const err)
{
    if (num > 1)
    {
        a_pid_set_num(ctx, num);
        a_pid_chan_(ctx, out, fdb, tmp, err);
    }
    else
    {
        a_pid_set_num(ctx, 0);
    }
    a_pid_zero_(ctx, num);
    return ctx;
}

a_pid_s *a_pid_init(a_pid_s *const ctx, a_float_t const dt, a_float_t const min, a_float_t const max)
{
    ctx->reg = A_PID_INC;
    ctx->outmin = min;
    ctx->outmax = max;
    ctx->summax = 0;
    ctx->num = 0;
    ctx->dt = dt;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    a_pid_zerof(ctx);
    return ctx;
}

void a_pid_zerof(a_pid_s *const ctx)
{
#define A_PID_ZERO(_) \
    ctx->out _ = 0;   \
    ctx->fdb _ = 0;   \
    ctx->tmp _ = 0;   \
    ctx->err _ = 0
    A_PID_ZERO(.f);
}

void a_pid_zerop(a_pid_s *const ctx, unsigned int const i)
{
    A_PID_ZERO(.p[i]);
}

void a_pid_zero_(a_pid_s *const ctx, unsigned int const num)
{
    if (num > 1)
    {
        for (unsigned int i = 0; i != num; ++i)
        {
            a_pid_zerop(ctx, i);
        }
    }
    else
    {
        a_pid_zerof(ctx);
    }
}

a_pid_s *a_pid_zero(a_pid_s *const ctx)
{
    a_pid_zero_(ctx, a_pid_num(ctx));
    return ctx;
}

void a_pid_outf_(a_pid_s *const ctx, unsigned int const mode, a_float_t const set, a_float_t const fdb, a_float_t const ec, a_float_t const e)
{
#define A_PID_OUT_(_)                                                                        \
    /* calculation */                                                                        \
    switch (mode)                                                                            \
    {                                                                                        \
    case A_PID_INC:                                                                          \
    {                                                                                        \
        a_float_t tmp = ctx->fdb _ - fdb;                                                    \
        ctx->out _ += ctx->kp * ec + ctx->ki * e + ctx->kd * (tmp - ctx->tmp _);             \
        ctx->tmp _ = tmp;                                                                    \
        break;                                                                               \
    }                                                                                        \
    case A_PID_POS:                                                                          \
    {                                                                                        \
        a_float_t const sum = ctx->ki * e;                                                   \
        /* when the limit of integration is exceeded or */                                   \
        /* the direction of integration is the same, the integration stops. */               \
        if ((-ctx->summax < ctx->tmp _ && ctx->tmp _ < ctx->summax) || ctx->tmp _ * sum < 0) \
        {                                                                                    \
            ctx->tmp _ += sum; /* sum = K_i[\sum^k_{i=0}e(i)] */                             \
        }                                                                                    \
        /* avoid derivative kick, fdb[k-1]-fdb[k] */                                         \
        /* out = K_p[e(k)]+sum+K_d[fdb(k-1)-fdb(k)] */                                       \
        ctx->out _ = ctx->kp * e + ctx->tmp _ + ctx->kd * (ctx->fdb _ - fdb);                \
        break;                                                                               \
    }                                                                                        \
    case A_PID_OFF:                                                                          \
    default:                                                                                 \
        ctx->out _ = set;                                                                    \
        ctx->tmp _ = 0;                                                                      \
    }                                                                                        \
    ctx->out _ = A_SAT(ctx->out _, ctx->outmin, ctx->outmax);                                \
    ctx->fdb _ = fdb;                                                                        \
    ctx->err _ = e
    A_PID_OUT_(.f);
}

void a_pid_outp_(a_pid_s *const ctx, unsigned int const mode, a_float_t const set, a_float_t const fdb, a_float_t const ec, a_float_t const e, unsigned int const i)
{
    A_PID_OUT_(.p[i]);
}

a_float_t a_pid_outf(a_pid_s *const ctx, a_float_t const set, a_float_t const fdb)
{
    a_float_t const e = set - fdb;
    a_pid_outf_(ctx, a_pid_mode(ctx), set, fdb, e - ctx->err.f, e);
    return ctx->out.f;
}

a_float_t const *a_pid_outp(a_pid_s *const ctx, a_float_t const *const set, a_float_t const *const fdb)
{
    unsigned int const num = a_pid_num(ctx);
    unsigned int const mode = a_pid_mode(ctx);
    for (unsigned int i = 0; i != num; ++i)
    {
        a_float_t const e = set[i] - fdb[i];
        a_pid_outp_(ctx, mode, set[i], fdb[i], e - ctx->err.p[i], e, i);
    }
    return ctx->out.p;
}
