#define LIBA_VERSION_C
#include "a/version.h"

char const *a_version(void)
{
    return A_VERSION;
}

unsigned int a_version_major(void)
{
    return A_VERSION_MAJOR;
}

unsigned int a_version_minor(void)
{
    return A_VERSION_MINOR;
}

unsigned int a_version_patch(void)
{
    return A_VERSION_PATCH;
}

int a_version_cmp(a_version_s const *const lhs, a_version_s const *const rhs)
{
    if (lhs->major < rhs->major)
    {
        return -3;
    }
    if (lhs->major > rhs->major)
    {
        return +3;
    }
    if (lhs->minor < rhs->minor)
    {
        return -2;
    }
    if (lhs->minor > rhs->minor)
    {
        return +2;
    }
    if (lhs->patch < rhs->patch)
    {
        return -1;
    }
    if (lhs->patch > rhs->patch)
    {
        return +1;
    }
    return 0;
}

#include <stdlib.h>

unsigned int a_version_parse(a_version_s *const ctx, char const *const ver)
{
    union
    {
        char const *p;
        char *s;
    } u = {ver};
    ctx->major = 0;
    ctx->minor = 0;
    ctx->patch = 0;
    if (ver)
    {
        ctx->major = (unsigned int)strtoul(u.p, &u.s, 0);
        if (u.p[0] == '.' && u.p[1] >= '0' && u.p[1] <= '9')
        {
            ++u.p;
        }
        else
        {
            goto done;
        }
        ctx->minor = (unsigned int)strtoul(u.p, &u.s, 0);
        if (u.p[0] == '.' && u.p[1] >= '0' && u.p[1] <= '9')
        {
            ++u.p;
        }
        else
        {
            goto done;
        }
        ctx->patch = (unsigned int)strtoul(u.p, &u.s, 0);
    done:
        return (unsigned int)(u.p - ver);
    }
    return 0;
}

#undef a_version_check
int a_version_check(unsigned int const major, unsigned int const minor, unsigned int const patch)
{
    a_version_s inner = A_VERSION_C(0, 0, 0);
    a_version_s outer = A_VERSION_C(0, 0, 0);
    inner.major = a_version_major();
    inner.minor = a_version_minor();
    inner.patch = a_version_patch();
    outer.major = major;
    outer.minor = minor;
    outer.patch = patch;
    return a_version_cmp(&inner, &outer);
}
