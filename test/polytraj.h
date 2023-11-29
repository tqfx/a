#define MAIN_(x) A_CAST_2(x, _polytraj)
#include "test.h"
#include "a/polytraj.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    int start = 1;
    if (argc > 1)
    {
        char *endptr = A_NULL;
#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
        (void)strtof(argv[1], &endptr);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
        (void)strtod(argv[1], &endptr);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
        (void)strtold(argv[1], &endptr);
#endif /* A_FLOAT_TYPE */
        if (argv[1] == endptr)
        {
            test_init(argc, argv, 1);
            ++start;
        }
    }

    a_float_t arg[10] = {0};
    for (int i = start; i < argc; ++i)
    {
#if A_FLOAT_TYPE + 0 == A_FLOAT_SINGLE
        arg[i - start] = strtof(argv[i], A_NULL);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_DOUBLE
        arg[i - start] = strtod(argv[i], A_NULL);
#elif A_FLOAT_TYPE + 0 == A_FLOAT_EXTEND
        arg[i - start] = strtold(argv[i], A_NULL);
#endif /* A_FLOAT_TYPE */
    }
    a_polytraj3_s pt3;
    a_polytraj3_gen(&pt3, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5]);
    a_polytraj5_s pt5;
    a_polytraj5_gen(&pt5, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);
    a_polytraj7_s pt7;
    a_polytraj7_gen(&pt7, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
    for (a_float_t dt = arg[0], delta = (arg[1] - arg[0]) / 1000; dt < arg[1]; dt += delta) // NOLINT
    {
        debug(A_FLOAT_PRI("+", "f "), dt);
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f "),
              a_polytraj3_pos(&pt3, dt), a_polytraj3_vel(&pt3, dt), a_polytraj3_acc(&pt3, dt));
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f "),
              a_polytraj5_pos(&pt5, dt), a_polytraj5_vel(&pt5, dt), a_polytraj5_acc(&pt5, dt));
        debug(A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f ") A_FLOAT_PRI("+", "f\n"),
              a_polytraj7_pos(&pt7, dt), a_polytraj7_vel(&pt7, dt), a_polytraj7_acc(&pt7, dt), a_polytraj7_jer(&pt7, dt));
    }

    return 0;
}
