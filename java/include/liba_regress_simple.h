/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_regress_simple */

#ifndef _Included_liba_regress_simple
#define _Included_liba_regress_simple
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_regress_simple
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_regress_1simple_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_regress_simple
 * Method:    init
 * Signature: (DD)V
 */
JNIEXPORT void JNICALL Java_liba_regress_1simple_init
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_regress_simple
 * Method:    coef
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_regress_1simple_coef
  (JNIEnv *, jobject);

/*
 * Class:     liba_regress_simple
 * Method:    set_coef
 * Signature: (D)Lliba/regress_simple;
 */
JNIEXPORT jobject JNICALL Java_liba_regress_1simple_set_1coef
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_regress_simple
 * Method:    bias
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_regress_1simple_bias
  (JNIEnv *, jobject);

/*
 * Class:     liba_regress_simple
 * Method:    set_bias
 * Signature: (D)Lliba/regress_simple;
 */
JNIEXPORT jobject JNICALL Java_liba_regress_1simple_set_1bias
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_regress_simple
 * Method:    eval
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_regress_1simple_eval
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_regress_simple
 * Method:    evar
 * Signature: (D)D
 */
JNIEXPORT jdouble JNICALL Java_liba_regress_1simple_evar
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_regress_simple
 * Method:    ols_
 * Signature: ([D[DDD)Lliba/regress_simple;
 */
JNIEXPORT jobject JNICALL Java_liba_regress_1simple_ols_1
  (JNIEnv *, jobject, jdoubleArray, jdoubleArray, jdouble, jdouble);

/*
 * Class:     liba_regress_simple
 * Method:    olsx
 * Signature: ([D[DD)Lliba/regress_simple;
 */
JNIEXPORT jobject JNICALL Java_liba_regress_1simple_olsx
  (JNIEnv *, jobject, jdoubleArray, jdoubleArray, jdouble);

/*
 * Class:     liba_regress_simple
 * Method:    olsy
 * Signature: ([D[DD)Lliba/regress_simple;
 */
JNIEXPORT jobject JNICALL Java_liba_regress_1simple_olsy
  (JNIEnv *, jobject, jdoubleArray, jdoubleArray, jdouble);

/*
 * Class:     liba_regress_simple
 * Method:    ols
 * Signature: ([D[D)Lliba/regress_simple;
 */
JNIEXPORT jobject JNICALL Java_liba_regress_1simple_ols
  (JNIEnv *, jobject, jdoubleArray, jdoubleArray);

/*
 * Class:     liba_regress_simple
 * Method:    zero
 * Signature: ()Lliba/regress_simple;
 */
JNIEXPORT jobject JNICALL Java_liba_regress_1simple_zero
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif