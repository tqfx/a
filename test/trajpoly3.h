#define MAIN_(x) A_CAST_2(x, _trajpoly3)
#include "test.h"
#include "a/trajpoly3.h"

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    int start = 1;
    if (argc > 1)
    {
        char *endptr = A_NULL;
        (void)strtonum(argv[1], &endptr);
        if (argv[1] == endptr)
        {
            main_init(argc, argv, 1);
            ++start;
        }
    }

    a_float arg[6] = {0};
    for (int i = start; i < argc; ++i)
    {
        arg[i - start] = strtonum(argv[i], A_NULL);
    }
    a_trajpoly3 ctx;
    a_trajpoly3_gen(&ctx, arg[1] - arg[0], arg[2], arg[3], arg[4], arg[5]);
    for (a_float dt = arg[0], delta = (arg[1] - arg[0]) / 1000; dt < arg[1]; dt += delta) // NOLINT
    {
        debug(A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f,") A_FLOAT_PRI("+", "f\n"),
              dt, a_trajpoly3_pos(&ctx, dt), a_trajpoly3_vel(&ctx, dt), a_trajpoly3_acc(&ctx, dt));
    }

#if defined(__cplusplus) && (__cplusplus > 201100L)
    A_ASSERT_BUILD(std::is_pod<a_trajpoly3>::value);
#endif /* __cplusplus */

    return 0;
}