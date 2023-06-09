#ifndef TEST_PID_FUZZY_H
#define TEST_PID_FUZZY_H
#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */
#define MAIN_(s, argc, argv) pid_fuzzy##s(argc, argv)
#include "test.h"
#include "a/tf.h"
#include "a/pid_fuzzy.h"

#undef NB
#undef NM
#undef NS
#undef ZO
#undef PS
#undef PM
#undef PB
#define NB -3 * S
#define NM -2 * S
#define NS -1 * S
#define ZO +0 * S
#define PS +1 * S
#define PM +2 * S
#define PB +3 * S
#undef S
#define S 1
static a_float_t const m7e[] = {
    A_MF_TRI, NB, NB, NM,
    A_MF_TRI, NB, NM, NS,
    A_MF_TRI, NM, NS, ZO,
    A_MF_TRI, NS, ZO, PS,
    A_MF_TRI, ZO, PS, PM,
    A_MF_TRI, PS, PM, PB,
    A_MF_TRI, PM, PB, PB};
#undef S
#define S 2
static a_float_t const m7ec[] = {
    A_MF_TRI, NB, NB, NM,
    A_MF_TRI, NB, NM, NS,
    A_MF_TRI, NM, NS, ZO,
    A_MF_TRI, NS, ZO, PS,
    A_MF_TRI, ZO, PS, PM,
    A_MF_TRI, PS, PM, PB,
    A_MF_TRI, PM, PB, PB};
#undef S
#define S A_FLOAT_C(10.0) / 3
static a_float_t const m7kp[] = {
    NB, NB, NM, NM, NS, ZO, ZO,
    NB, NB, NM, NS, NS, ZO, PS,
    NM, NM, NM, NS, ZO, PS, PS,
    NM, NM, NS, ZO, PS, PM, PM,
    NS, NS, ZO, PS, PS, PM, PM,
    NS, ZO, PS, PM, PM, PM, PB,
    ZO, ZO, PM, PM, PM, PB, PB};
#undef S
#define S A_FLOAT_C(0.01) / 3
static a_float_t const m7ki[] = {
    PB, PB, PM, PM, PS, ZO, ZO,
    PB, PB, PM, PS, PS, ZO, ZO,
    PB, PM, PS, PS, ZO, NS, NS,
    PM, PM, PS, ZO, NS, NM, NM,
    PM, PS, ZO, NS, NS, NM, NB,
    ZO, ZO, NS, NS, NM, NB, NB,
    ZO, ZO, NS, NM, NM, NB, NB};
#undef S
#define S A_FLOAT_C(0.1) / 3
static a_float_t const m7kd[] = {
    NS, PS, PB, PB, PB, PM, NS,
    NS, PS, PB, PM, PM, PS, ZO,
    ZO, PS, PM, PM, PS, PS, ZO,
    ZO, PS, PS, PS, PS, PS, ZO,
    ZO, ZO, ZO, ZO, ZO, ZO, ZO,
    NB, NS, NS, NS, NS, NS, NB,
    NB, NM, NM, NM, NS, NS, NB};
#undef S

static void test_f(void)
{
    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t u[a_count_of(num)] = {0};
    a_float_t v[a_count_of(den)] = {0};
    a_tf_s tf;
    a_tf_init(&tf, a_count_of(num), num, u, a_count_of(den), den, v);
    a_pid_fuzzy_s ctx;
    a_pid_fuzzy_init(&ctx, A_FLOAT_C(0.01), 7, m7e, m7ec, m7kp, m7ki, m7kd, -10, +10);
    {
        static unsigned int idx[A_PID_FUZZY_IDX(2)];
        static a_float_t val[A_PID_FUZZY_VAL(2)];
        a_pid_fuzzy_buff(&ctx, idx, val);
        a_pid_fuzzy_pos(&ctx, 10);
    }
    a_pid_fuzzy_kpid(&ctx, 400, 200, A_FLOAT_C(0.005));
    a_pid_set_dt(&ctx.pid, A_FLOAT_C(0.001));
    for (a_float_t t = 0; t < A_FLOAT_C(0.2); t += A_FLOAT_C(0.001))
    {
        a_tf_iter(&tf, a_pid_fuzzy_outf(&ctx, 1, v[0]));
    }
    a_tf_zero(&tf);
    a_pid_fuzzy_zero(&ctx);
    char buff[A_PID_FUZZY_BUF1(2)];
    a_pid_fuzzy_buf1(&ctx, buff, 2);
    for (a_float_t t = 0; t < A_FLOAT_C(0.2); t += A_FLOAT_C(0.001))
    {
        u[0] = a_pid_fuzzy_outf(&ctx, 1, v[0]);
        v[0] = a_tf_iter(&tf, u[0]);
    }
    TEST_BUG(a_pid_fuzzy_op(&ctx) == A_PID_FUZZY_EQU);
    a_pid_fuzzy_set_op(&ctx, A_PID_FUZZY_OR_DEFAULT);
    TEST_BUG(a_pid_fuzzy_op(&ctx) == A_PID_FUZZY_OR_DEFAULT);
    a_pid_fuzzy_set_op(&ctx, A_PID_FUZZY_OR_ALGEBRA);
    TEST_BUG(a_pid_fuzzy_op(&ctx) == A_PID_FUZZY_OR_ALGEBRA);
    a_pid_fuzzy_set_op(&ctx, A_PID_FUZZY_OR_BOUNDED);
    TEST_BUG(a_pid_fuzzy_op(&ctx) == A_PID_FUZZY_OR_BOUNDED);
    a_pid_fuzzy_set_op(&ctx, A_PID_FUZZY_AND_DEFAULT);
    TEST_BUG(a_pid_fuzzy_op(&ctx) == A_PID_FUZZY_AND_DEFAULT);
    a_pid_fuzzy_set_op(&ctx, A_PID_FUZZY_AND_ALGEBRA);
    TEST_BUG(a_pid_fuzzy_op(&ctx) == A_PID_FUZZY_AND_ALGEBRA);
    a_pid_fuzzy_set_op(&ctx, A_PID_FUZZY_AND_BOUNDED);
    TEST_BUG(a_pid_fuzzy_op(&ctx) == A_PID_FUZZY_AND_BOUNDED);
    a_pid_fuzzy_exit(&ctx);
}

static void test_p(void)
{
    a_float_t num0[] = {A_FLOAT_C(5.59492796e-05), A_FLOAT_C(5.54019884e-05)};
    a_float_t den0[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t num1[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den1[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t num2[] = {A_FLOAT_C(7.59492796e-05), A_FLOAT_C(7.54019884e-05)};
    a_float_t den2[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t u0[a_count_of(num0)] = {0};
    a_float_t v0[a_count_of(den0)] = {0};
    a_float_t u1[a_count_of(num1)] = {0};
    a_float_t v1[a_count_of(den1)] = {0};
    a_float_t u2[a_count_of(num2)] = {0};
    a_float_t v2[a_count_of(den2)] = {0};
    a_tf_s tf[3];
    a_tf_init(tf + 0, a_count_of(num0), num0, u0, a_count_of(den0), den0, v0);
    a_tf_init(tf + 1, a_count_of(num1), num1, u1, a_count_of(den1), den1, v1);
    a_tf_init(tf + 2, a_count_of(num2), num2, u2, a_count_of(den2), den2, v2);
    a_pid_fuzzy_s ctx;
    a_pid_fuzzy_init(&ctx, A_FLOAT_C(0.01), 7, m7e, m7ec, m7kp, m7ki, m7kd, -10, +10);
    {
        static unsigned int idx[A_PID_FUZZY_IDX(2)];
        static a_float_t val[A_PID_FUZZY_VAL(2)];
        a_pid_fuzzy_buff(&ctx, idx, val);
        a_pid_fuzzy_pos(&ctx, 10);
    }
    a_pid_fuzzy_kpid(&ctx, 400, 200, A_FLOAT_C(0.005));
    a_pid_set_dt(&ctx.pid, A_FLOAT_C(0.001));
    {
        static a_float_t out[3];
        static a_float_t fdb[3];
        static a_float_t tmp[3];
        static a_float_t err[3];
        a_pid_fuzzy_chan(&ctx, 3, out, fdb, tmp, err);
    }
    a_float_t set[3] = {1, 1, 1};
    for (a_float_t t = 0; t < A_FLOAT_C(0.4); t += A_FLOAT_C(0.001))
    {
        a_float_t fdb[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            fdb[i] = *tf[i].v;
        }
        a_float_t const *const out = a_pid_fuzzy_outp(&ctx, set, fdb);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + i, out[i]);
        }
    }
    a_pid_fuzzy_exit(&ctx);
}

static A_INLINE a_float_t input(a_float_t const x)
{
#if 0
    return a_float_sin(4 * A_FLOAT_PI * x);
#else
    return (void)x, 1;
#endif
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
#if defined(MAIN_ONCE)
    FILE *log = A_NULL;
    if (argc > 1)
    {
        log = freopen(argv[1], "wb", stdout);
    }
#else /* !MAIN_ONCE */
    (void)(argc);
    (void)(argv);
#endif /* MAIN_ONCE */
    test_f();
    test_p();

    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};

    a_tf_s pos_tf;
    a_float_t pos_u[a_count_of(num)] = {0};
    a_float_t pos_v[a_count_of(den)] = {0};
    a_tf_init(&pos_tf, a_count_of(num), num, pos_u, a_count_of(den), den, pos_v);
    a_tf_s inc_tf;
    a_float_t inc_u[a_count_of(num)] = {0};
    a_float_t inc_v[a_count_of(den)] = {0};
    a_tf_init(&inc_tf, a_count_of(num), num, inc_u, a_count_of(den), den, inc_v);

    a_pid_fuzzy_s pos_7;
    a_pid_fuzzy_s inc_7;
    a_pid_fuzzy_init(&pos_7, A_FLOAT_C(0.001), 7, m7e, m7ec, m7kp, m7ki, m7kd, -10, +10);
    {
        static unsigned int idx[A_PID_FUZZY_IDX(2)];
        static a_float_t val[A_PID_FUZZY_VAL(2)];
        a_pid_fuzzy_buff(&pos_7, idx, val);
        a_pid_fuzzy_pos(&pos_7, 10);
    }
    a_pid_fuzzy_init(&inc_7, A_FLOAT_C(0.001), 7, m7e, m7ec, m7kp, m7ki, m7kd, -10, +10);
    {
        static unsigned int idx[A_PID_FUZZY_IDX(2)];
        static a_float_t val[A_PID_FUZZY_VAL(2)];
        a_pid_fuzzy_buff(&inc_7, idx, val);
        a_pid_fuzzy_inc(&inc_7);
    }
    a_pid_fuzzy_kpid(&pos_7, 10, A_FLOAT_C(0.01), A_FLOAT_C(0.1));
    a_pid_fuzzy_kpid(&inc_7, 9, A_FLOAT_C(0.01), A_FLOAT_C(0.09));
    for (a_float_t t = 0; t < A_FLOAT_C(0.5); t += A_FLOAT_C(0.001))
    {
        a_float_t in = input(t);
        a_tf_iter(&pos_tf, a_pid_fuzzy_outf(&pos_7, in, *pos_tf.v));
        a_tf_iter(&inc_tf, a_pid_fuzzy_outf(&inc_7, in, *inc_tf.v));
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), t, in, *pos_tf.v, *inc_tf.v);
#endif /* MAIN_ONCE */
    }
    a_pid_fuzzy_exit(&pos_7);
    a_pid_fuzzy_exit(&inc_7);

#if defined(MAIN_ONCE)
    if (log)
    {
        if (fclose(log))
        {
            perror(A_FUNC);
        }
    }
#endif /* MAIN_ONCE */

    return 0;
}

#endif /* pid_fuzzy.h */
