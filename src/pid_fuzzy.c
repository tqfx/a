#include "a/pid_fuzzy.h"
#include "a/fuzzy.h"
#include "a/math.h"
#include "a/mf.h"

A_HIDDEN a_float a_pid_fuzzy_equ(a_float a, a_float b);
a_float a_pid_fuzzy_equ(a_float const a, a_float const b)
{
    return a_float_sqrt(a * b) * a_float_sqrt(1 - (1 - a) * (1 - b));
}

a_float (*a_pid_fuzzy_op(unsigned int const op))(a_float, a_float)
{
    switch (op)
    {
    case A_PID_FUZZY_CUP_BOUNDED:
        return a_fuzzy_cup_bounded;
    case A_PID_FUZZY_CUP_ALGEBRA:
        return a_fuzzy_cup_algebra;
    case A_PID_FUZZY_CUP:
        return a_fuzzy_cup;
    case A_PID_FUZZY_CAP_BOUNDED:
        return a_fuzzy_cap_bounded;
    case A_PID_FUZZY_CAP_ALGEBRA:
        return a_fuzzy_cap_algebra;
    case A_PID_FUZZY_CAP:
        return a_fuzzy_cap;
    case A_PID_FUZZY_EQU:
    default:
        return a_pid_fuzzy_equ;
    }
}

void a_pid_fuzzy_set_op(a_pid_fuzzy *const ctx, unsigned int const op) { ctx->op = a_pid_fuzzy_op(op); }

A_HIDDEN unsigned int a_pid_fuzzy_mf(a_float x, unsigned int n, a_float const *a, unsigned int *idx, a_float *val);
unsigned int a_pid_fuzzy_mf(a_float const x, unsigned int const n, a_float const *a, unsigned int *idx, a_float *val)
{
    unsigned int counter = 0;
    for (unsigned int i = 0; i != n; ++i)
    {
        a_float y = 0;
        switch ((int)*a++)
        {
        case A_MF_GAUSS:
            y = a_mf_gauss(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_GAUSS2:
            y = a_mf_gauss2(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_GBELL:
            y = a_mf_gbell(x, a[0], a[1], a[2]);
            a += 3;
            break;
        case A_MF_SIG:
            y = a_mf_sig(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_DSIG:
            y = a_mf_dsig(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_PSIG:
            y = a_mf_psig(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_TRAP:
            y = a_mf_trap(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_TRI:
            y = a_mf_tri(x, a[0], a[1], a[2]);
            a += 3;
            break;
        case A_MF_LINS:
            y = a_mf_lins(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_LINZ:
            y = a_mf_linz(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_S:
            y = a_mf_s(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_Z:
            y = a_mf_z(x, a[0], a[1]);
            a += 2;
            break;
        case A_MF_PI:
            y = a_mf_pi(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        case A_MF_NUL:
        default:
            goto out;
        }
        if (y > A_FLOAT_EPSILON)
        {
            *idx++ = i;
            *val++ = y;
            ++counter;
        }
    }
out:
    return counter;
}

void a_pid_fuzzy_zero(a_pid_fuzzy *const ctx) { a_pid_zero(&ctx->pid); }

void a_pid_fuzzy_init(a_pid_fuzzy *const ctx) { a_pid_init(&ctx->pid); }

void a_pid_fuzzy_rule(a_pid_fuzzy *const ctx, unsigned int const order, a_float const *const me, a_float const *const mec,
                      a_float const *const mkp, a_float const *const mki, a_float const *const mkd)
{
    ctx->me = me;
    ctx->mec = mec;
    ctx->mkp = mkp;
    ctx->mki = mki;
    ctx->mkd = mkd;
    ctx->order = order;
}

void *a_pid_fuzzy_joint(a_pid_fuzzy *const ctx) { return ctx->idx; }
void a_pid_fuzzy_set_joint(a_pid_fuzzy *const ctx, void *ptr, a_size const num)
{
    ctx->joint = (unsigned int)num;
    ctx->idx = (unsigned int *)ptr;
    ptr = (a_byte *)ptr + sizeof(unsigned int) * 2 * num;
    ctx->val = (a_float *)ptr;
}

void a_pid_fuzzy_kpid(a_pid_fuzzy *const ctx, a_float const kp, a_float const ki, a_float const kd)
{
    a_pid_kpid(&ctx->pid, kp, ki, kd);
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

A_HIDDEN void a_pid_fuzzy_out_(a_pid_fuzzy *const ctx, a_float ec, a_float e);
void a_pid_fuzzy_out_(a_pid_fuzzy *const ctx, a_float const ec, a_float const e)
{
    a_float kp = 0;
    a_float ki = 0;
    a_float kd = 0;
    /* calculate membership */
    unsigned int const ne = a_pid_fuzzy_mf(e, ctx->order, ctx->me, ctx->idx, ctx->val);
    if (!ne) { goto pid; }
    unsigned int *const idx = ctx->idx + ne;
    a_float *const val = ctx->val + ne;
    unsigned int const nec = a_pid_fuzzy_mf(ec, ctx->order, ctx->mec, idx, val);
    if (!nec) { goto pid; }
    a_float *const mat = val + nec;
    /* joint membership */
    a_float inv = 0;
    {
        a_float *it = mat;
        for (unsigned int i = 0; i != ne; ++i)
        {
            for (unsigned int j = 0; j != nec; ++j)
            {
                *it = ctx->op(ctx->val[i], val[j]); /* mat(i,j)=f(e[i],ec[j]) */
                inv += *it++;
            }
            ctx->idx[i] *= ctx->order;
        }
    }
    inv = 1 / inv;
    /* mean of centers defuzzifier */
    if (ctx->mkp)
    {
        a_float const *it = mat;
        for (unsigned int i = 0; i != ne; ++i)
        {
            a_float const *const mkp = ctx->mkp + ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j)
            {
                kp += *it++ * mkp[idx[j]]; /* += mat(i,j) * mkp(e[i],ec[j]) */
            }
        }
        kp *= inv;
    }
    if (ctx->mki)
    {
        a_float const *it = mat;
        for (unsigned int i = 0; i != ne; ++i)
        {
            a_float const *const mki = ctx->mki + ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j)
            {
                ki += *it++ * mki[idx[j]]; /* += mat(i,j) * mki(e[i],ec[j]) */
            }
        }
        ki *= inv;
    }
    if (ctx->mkd)
    {
        a_float const *it = mat;
        for (unsigned int i = 0; i != ne; ++i)
        {
            a_float const *const mkd = ctx->mkd + ctx->idx[i];
            for (unsigned int j = 0; j != nec; ++j)
            {
                kd += *it++ * mkd[idx[j]]; /* += mat(i,j) * mkd(e[i],ec[j]) */
            }
        }
        kd *= inv;
    }
pid:
    a_pid_kpid(&ctx->pid, ctx->kp + kp, ctx->ki + ki, ctx->kd + kd);
}

A_HIDDEN a_float a_pid_run_(a_pid *ctx, a_float set, a_float fdb, a_float err);
a_float a_pid_fuzzy_run(a_pid_fuzzy *const ctx, a_float const set, a_float const fdb)
{
    a_float const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_run_(&ctx->pid, set, fdb, err);
}

A_HIDDEN a_float a_pid_pos_(a_pid *ctx, a_float fdb, a_float err);
a_float a_pid_fuzzy_pos(a_pid_fuzzy *const ctx, a_float const set, a_float const fdb)
{
    a_float const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_pos_(&ctx->pid, fdb, err);
}

A_HIDDEN a_float a_pid_inc_(a_pid *ctx, a_float fdb, a_float err);
a_float a_pid_fuzzy_inc(a_pid_fuzzy *const ctx, a_float const set, a_float const fdb)
{
    a_float const err = set - fdb;
    a_pid_fuzzy_out_(ctx, err - ctx->pid.err, err);
    return a_pid_inc_(&ctx->pid, fdb, err);
}
