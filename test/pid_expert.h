#ifndef TEST_PID_EXPERT_H
#define TEST_PID_EXPERT_H
#define MAIN_(s, argc, argv) A_CASE_2(pid_expert, s)(argc, argv)
#include "test.h"
#include "a/tf.h"
#include "a/math.h"
#include "a/pid_expert.h"

static void test_f(void)
{
    a_float_t num[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t input[a_count_of(num)];
    a_float_t output[a_count_of(den)];
    a_tf_s tf;
    a_tf_init(&tf, a_count_of(num), num, input, a_count_of(den), den, output);
    a_pid_expert_s ctx;
    a_pid_expert_init(&ctx, A_FLOAT_C(0.01), -10, +10, A_FLOAT_C(0.01), A_FLOAT_C(0.6), A_FLOAT_C(2.0), A_FLOAT_C(0.1), A_FLOAT_C(0.5));
    a_pid_expert_kpid(&ctx, 400, 200, A_FLOAT_C(0.005));
    a_pid_set_dt(&ctx.pid, A_FLOAT_C(0.001));
    for (a_float_t t = 0; t < A_FLOAT_C(0.2); t += A_FLOAT_C(0.001))
    {
        a_tf_iter(&tf, a_pid_expert_outf(&ctx, 1, output[0]));
    }
    a_pid_expert_zero(&ctx);
    a_tf_zero(&tf);
}

static void test_p(void)
{
    a_float_t num0[] = {A_FLOAT_C(5.59492796e-05), A_FLOAT_C(5.54019884e-05)};
    a_float_t den0[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t num1[] = {A_FLOAT_C(6.59492796e-05), A_FLOAT_C(6.54019884e-05)};
    a_float_t den1[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t num2[] = {A_FLOAT_C(7.59492796e-05), A_FLOAT_C(7.54019884e-05)};
    a_float_t den2[] = {A_FLOAT_C(-1.97530991), A_FLOAT_C(0.97530991)};
    a_float_t input0[a_count_of(num0)];
    a_float_t output0[a_count_of(den0)];
    a_float_t input1[a_count_of(num1)];
    a_float_t output1[a_count_of(den1)];
    a_float_t input2[a_count_of(num2)];
    a_float_t output2[a_count_of(den2)];
    a_tf_s tf[3];
    a_tf_init(tf + 0, a_count_of(num0), num0, input0, a_count_of(den0), den0, output0);
    a_tf_init(tf + 1, a_count_of(num1), num1, input1, a_count_of(den1), den1, output1);
    a_tf_init(tf + 2, a_count_of(num2), num2, input2, a_count_of(den2), den2, output2);
    a_pid_expert_s ctx;
    a_pid_expert_init(&ctx, A_FLOAT_C(0.01), -10, +10, A_FLOAT_C(0.01), A_FLOAT_C(0.6), A_FLOAT_C(2.0), A_FLOAT_C(0.1), A_FLOAT_C(0.5));
    a_pid_expert_kpid(&ctx, 10, A_FLOAT_C(0.01), A_FLOAT_C(0.1));
    a_pid_set_dt(&ctx.pid, A_FLOAT_C(0.001));
    {
        static a_float_t out[3];
        static a_float_t fdb[3];
        static a_float_t tmp[3];
        static a_float_t err[3];
        static a_float_t ec[3];
        a_pid_expert_chan(&ctx, 3, out, fdb, tmp, err, ec);
    }
    a_float_t set[3] = {1, 1, 1};
    for (a_float_t t = 0; t < A_FLOAT_C(0.4); t += A_FLOAT_C(0.001))
    {
        a_float_t fdb[3];
        for (unsigned int i = 0; i != 3; ++i)
        {
            fdb[i] = *tf[i].output;
        }
        a_float_t const *const out = a_pid_expert_outp(&ctx, set, fdb);
        for (unsigned int i = 0; i != 3; ++i)
        {
            a_tf_iter(tf + i, out[i]);
        }
    }
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

    a_tf_s tf;
    a_float_t tf_input[a_count_of(num)];
    a_float_t tf_output[a_count_of(den)];
    a_tf_init(&tf, a_count_of(num), num, tf_input, a_count_of(den), den, tf_output);

    a_pid_expert_s ctx;
    a_pid_expert_init(&ctx, A_FLOAT_C(0.001), -10, +10, A_FLOAT_C(0.4), A_FLOAT_C(2.0), A_FLOAT_C(0.2), A_FLOAT_C(0.5), A_FLOAT_C(0.01));
    a_pid_expert_kpid(&ctx, 10000, A_FLOAT_C(100.0), A_FLOAT_C(1.0));
    for (a_float_t t = 0; t < A_FLOAT_C(0.5); t += A_FLOAT_C(0.001))
    {
        a_float_t in = input(t);
        a_tf_iter(&tf, a_pid_expert_outf(&ctx, in, *tf.output));
#if defined(MAIN_ONCE)
        printf(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"), t, in, *tf.output, ctx.pid.err.f);
#endif /* MAIN_ONCE */
    }

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

#endif /* pid_expert.h */
