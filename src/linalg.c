#include "a/linalg.h"

void a_linalg_T1(a_float *A, a_uint n)
{
    a_uint r, c;
    for (r = 0; r < n; ++r)
    {
        a_float *const Ar = A + (a_size)n * r;
        for (c = r + 1; c < n; ++c)
        {
            a_float *const Ac = A + (a_size)n * c;
            a_float value;
            value = Ac[r];
            Ac[r] = Ar[c];
            Ar[c] = value;
        }
    }
}

void a_linalg_T2(a_float *__restrict T, a_float const *__restrict A, a_uint m, a_uint n)
{
    a_uint r, c;
    for (c = 0; c < n; ++c)
    {
        a_size const mc = (a_size)m * c;
        for (r = 0; r < m; ++r)
        {
            a_size const nr = (a_size)n * r;
            T[mc + r] = A[nr + c];
        }
    }
}

a_float a_linalg_dot(a_float const *X, a_float const *Y, a_size n)
{
    a_float res = 0;
    for (; n; --n)
    {
        res += *X++ * *Y++;
    }
    return res;
}

void a_linalg_mulmm(a_float *__restrict Z, a_float const *__restrict X, a_float const *__restrict Y, a_uint row, a_uint c_r, a_uint col)
{
    a_float const *x, *x_, *y, *y_;
    a_float *z, *z_ = Z + (a_size)row * col;
    for (z = Z; z < z_; ++z) { *z = 0; }
    for (x = X; row--; Z = z)
    {
        x_ = x + c_r;
        for (y = Y; x < x_; ++x)
        {
            y_ = y + col;
            for (z = Z; y < y_; ++y)
            {
                *z++ += *x * *y;
            }
        }
    }
}

void a_linalg_mulTm(a_float *__restrict Z, a_float const *__restrict X, a_float const *__restrict Y, a_uint c_r, a_uint row, a_uint col)
{
    a_float const *x, *x_, *y, *y_;
    a_float *z, *z_ = Z + (a_size)row * col;
    for (z = Z; z < z_; ++z) { *z = 0; }
    for (x = X; c_r--; Y = y_)
    {
        x_ = x + row;
        y_ = Y + col;
        for (z = Z; x < x_; ++x)
        {
            for (y = Y; y < y_; ++y)
            {
                *z++ += *x * *y;
            }
        }
    }
}

void a_linalg_mulmT(a_float *__restrict Z, a_float const *__restrict X, a_float const *__restrict Y, a_uint row, a_uint col, a_uint c_r)
{
    a_float const *x, *x_, *y, *y_ = Y + (a_size)col * c_r;
    a_float *z, *z_ = Z + (a_size)row * col;
    for (z = Z; z < z_; ++z) { *z = 0; }
    for (z = Z; row--; X = x_)
    {
        x_ = X + c_r;
        for (y = Y; y < y_; ++z)
        {
            for (x = X; x < x_; ++x)
            {
                *z += *x * *y++;
            }
        }
    }
}

void a_linalg_mulTT(a_float *__restrict Z, a_float const *__restrict X, a_float const *__restrict Y, a_uint row, a_uint c_r, a_uint col)
{
    a_uint const n = c_r;
    a_float const *x, *x_, *y, *y_ = Y + (a_size)col * c_r;
    a_float *z, *z_ = Z + (a_size)row * col;
    for (z = Z; z < z_; ++z) { *z = 0; }
    for (x = X; c_r--; ++Y)
    {
        x_ = x + row;
        for (z = Z; x < x_; ++x)
        {
            for (y = Y; y < y_; y += n)
            {
                *z++ += *x * *y;
            }
        }
    }
}
