/*!
 @file regress_linear.h
 @brief linear regression
 @details https://en.wikipedia.org/wiki/Linear_regression
*/

#ifndef LIBA_REGRESS_LINEAR_H
#define LIBA_REGRESS_LINEAR_H

#include "a.h"

/*!
 @ingroup a_regress
 @addtogroup a_regress_linear linear regression
 @{
*/

typedef struct a_regress_linear a_regress_linear;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief initialize for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] coef_p points to regression coefficients
 @param[in] coef_n number of regression coefficients
 @param[in] bias intercept
*/
A_EXTERN void a_regress_linear_init(a_regress_linear *ctx, a_float *coef_p, a_size coef_n, a_float bias);

/*!
 @brief calculate predicted value for linear regression
 @param[in] ctx points to an instance of linear regression
 @param[in] val input variables
 @return predicted value
*/
A_EXTERN a_float a_regress_linear_eval(a_regress_linear const *ctx, a_float const *val);

/*!
 @brief calculate residuals for linear regression
 @param[in] ctx points to an instance of linear regression
 @param[out] err residuals, specified as a numeric vector
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, err[n], y[n], x[n][coef_n]
*/
A_EXTERN void a_regress_linear_err1(a_regress_linear const *ctx, a_float *err, a_float const *y, a_float const *x, a_size n);

/*!
 @brief calculate residuals for linear regression
 @param[in] ctx points to an instance of linear regression
 @param[out] err residuals, specified as a numeric vector
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, err[n], y[n], x[coef_n*n]
*/
A_EXTERN void a_regress_linear_err2(a_regress_linear const *ctx, a_float *err, a_float const *y, a_float const *const *x, a_size n);

/*!
 @brief calculate prediction deviation from mean for linear regression
 @param[in] ctx points to an instance of linear regression
 @param[out] pdm deviation, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, pdm[n], x[n][coef_n]
 @param[in] y_mean mean of response data
*/
A_EXTERN void a_regress_linear_pdm1(a_regress_linear const *ctx, a_float *pdm, a_float const *x, a_size n, a_float y_mean);

/*!
 @brief calculate prediction deviation from mean for linear regression
 @param[in] ctx points to an instance of linear regression
 @param[out] pdm deviation, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, pdm[n], x[coef_n*n]
 @param[in] y_mean mean of response data
*/
A_EXTERN void a_regress_linear_pdm2(a_regress_linear const *ctx, a_float *pdm, a_float const *const *x, a_size n, a_float y_mean);

/*!
 @brief stochastic gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] error residual, specified as a numeric scalar
 @param[in] input predictor data, specified as a numeric vector
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_sgd_(a_regress_linear *ctx, a_float error, a_float const *input, a_float alpha);

/*!
 @brief stochastic gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] y response data, specified as a numeric scalar
 @param[in] x predictor data, specified as a numeric vector
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_sgd(a_regress_linear *ctx, a_float y, a_float const *x, a_float alpha);

/*!
 @brief stochastic gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, y[n], x[coef_n*n]
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_sgd1(a_regress_linear *ctx, a_float const *y, a_float const *x, a_size n, a_float alpha);

/*!
 @brief stochastic gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, y[n], x[n][coef_n]
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_sgd2(a_regress_linear *ctx, a_float const *y, a_float const *const *x, a_size n, a_float alpha);

/*!
 @brief batch gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] err residuals, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, err[n], x[coef_n*n]
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_bgd1(a_regress_linear *ctx, a_float const *err, a_float const *x, a_size n, a_float alpha);

/*!
 @brief batch gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[in] err residuals, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, err[n], x[n][coef_n]
 @param[in] alpha learning rate for gradient descent
*/
A_EXTERN void a_regress_linear_bgd2(a_regress_linear *ctx, a_float const *err, a_float const *const *x, a_size n, a_float alpha);

/*!
 @brief mini-batch gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[out] err residuals, specified as a numeric vector
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, err[n], y[n], x[coef_n*n]
 @param[in] alpha learning rate for gradient descent
 @param[in] delta threshold for gradient descent value
 @param[in] count maximum number of iterations
 @param[in] batch batch size of data
 @retval 1 `delta` < threshold
 @retval 0 reaching `count`
*/
A_EXTERN int a_regress_linear_mgd1(a_regress_linear *ctx, a_float *err, a_float const *y, a_float const *x,
                                   a_size n, a_float alpha, a_float delta, a_size count, a_size batch);

/*!
 @brief mini-batch gradient descent for linear regression
 @param[in,out] ctx points to an instance of linear regression
 @param[out] err residuals, specified as a numeric vector
 @param[in] y response data, specified as a numeric vector
 @param[in] x predictor data, specified as a numeric matrix
 @param[in] n number of samples, err[n], y[n], x[n][coef_n]
 @param[in] alpha learning rate for gradient descent
 @param[in] delta threshold for gradient descent value
 @param[in] count maximum number of iterations
 @param[in] batch batch size of data
 @retval 1 `delta` < threshold
 @retval 0 reaching `count`
*/
A_EXTERN int a_regress_linear_mgd2(a_regress_linear *ctx, a_float *err, a_float const *y, a_float const *const *x,
                                   a_size n, a_float alpha, a_float delta, a_size count, a_size batch);

/*!
 @brief zeroing for linear regression
 @param[in,out] ctx points to an instance of linear regression
*/
A_EXTERN void a_regress_linear_zero(a_regress_linear *ctx);

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{
typedef struct a_regress_linear regress_linear;
} /* namespace a */
#endif /* __cplusplus */

/*!
 @brief instance structure for linear regression
*/
struct a_regress_linear
{
    a_float *coef_p; // points to regression coefficients
    a_size coef_n; // number of regression coefficients
    a_float bias; // intercept
#if defined(__cplusplus)
    A_INLINE void init(a_float *p, a_size n, a_float b = 0)
    {
        a_regress_linear_init(this, p, n, b);
    }
    A_INLINE a_float eval(a_float const *val) const
    {
        return a_regress_linear_eval(this, val);
    }
    A_INLINE void err1(a_float *err, a_float const *y, a_float const *x, a_size n) const
    {
        a_regress_linear_err1(this, err, y, x, n);
    }
    A_INLINE void err2(a_float *err, a_float const *y, a_float const *const *x, a_size n) const
    {
        a_regress_linear_err2(this, err, y, x, n);
    }
    A_INLINE void pdm1(a_float *pdm, a_float const *x, a_size n, a_float y_mean) const
    {
        a_regress_linear_pdm1(this, pdm, x, n, y_mean);
    }
    A_INLINE void pdm2(a_float *pdm, a_float const *const *x, a_size n, a_float y_mean) const
    {
        a_regress_linear_pdm2(this, pdm, x, n, y_mean);
    }
    A_INLINE void sgd_(a_float error, a_float const *input, a_float alpha)
    {
        a_regress_linear_sgd_(this, error, input, alpha);
    }
    A_INLINE void sgd(a_float y, a_float const *x, a_float alpha)
    {
        a_regress_linear_sgd(this, y, x, alpha);
    }
    A_INLINE void sgd1(a_float const *y, a_float const *x, a_size n, a_float alpha)
    {
        a_regress_linear_sgd1(this, y, x, n, alpha);
    }
    A_INLINE void sgd2(a_float const *y, a_float const *const *x, a_size n, a_float alpha)
    {
        a_regress_linear_sgd2(this, y, x, n, alpha);
    }
    A_INLINE void bgd1(a_float const *err, a_float const *x, a_size n, a_float alpha)
    {
        a_regress_linear_bgd1(this, err, x, n, alpha);
    }
    A_INLINE void bgd2(a_float const *err, a_float const *const *x, a_size n, a_float alpha)
    {
        a_regress_linear_bgd2(this, err, x, n, alpha);
    }
    A_INLINE int mgd1(a_float *err, a_float const *y, a_float const *x, a_size n,
                      a_float alpha, a_float delta, a_size count, a_size batch)
    {
        return a_regress_linear_mgd1(this, err, y, x, n, alpha, delta, count, batch);
    }
    A_INLINE int mgd2(a_float *err, a_float const *y, a_float const *const *x, a_size n,
                      a_float alpha, a_float delta, a_size count, a_size batch)
    {
        return a_regress_linear_mgd2(this, err, y, x, n, alpha, delta, count, batch);
    }
    A_INLINE void zero() { a_regress_linear_zero(this); }
#endif /* __cplusplus */
};

/*! @} a_regress_linear */

#endif /* a/regress_linear.h */
