/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class liba_pid_fuzzy */

#ifndef _Included_liba_pid_fuzzy
#define _Included_liba_pid_fuzzy
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     liba_pid_fuzzy
 * Method:    clinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_clinit
  (JNIEnv *, jclass);

/*
 * Class:     liba_pid_fuzzy
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_liba_pid_1fuzzy_init
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    kp
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kp__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    kp
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kp__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    ki
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_ki__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    ki
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_ki__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    kd
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_kd__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    kd
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kd__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    summax
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summax__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    summax
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summax__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    summin
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_summin__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    summin
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_summin__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    sum
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_sum
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    outmax
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmax__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    outmax
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmax__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    outmin
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_outmin__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    outmin
 * Signature: (D)Lliba/pid;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_outmin__D
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    out
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_out
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    fdb
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_fdb
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    err
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_err
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    nrule
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_nrule
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    opr
 * Signature: (I)Lliba/pid_fuzzy;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_opr
  (JNIEnv *, jobject, jint);

/*
 * Class:     liba_pid_fuzzy
 * Method:    rule
 * Signature: ([[D[[D[[D[[D[[D)Lliba/pid_fuzzy;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_rule
  (JNIEnv *, jobject, jobjectArray, jobjectArray, jobjectArray, jobjectArray, jobjectArray);

/*
 * Class:     liba_pid_fuzzy
 * Method:    nfuzz
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_liba_pid_1fuzzy_nfuzz__
  (JNIEnv *, jobject);

/*
 * Class:     liba_pid_fuzzy
 * Method:    nfuzz
 * Signature: (I)Lliba/pid_fuzzy;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_nfuzz__I
  (JNIEnv *, jobject, jint);

/*
 * Class:     liba_pid_fuzzy
 * Method:    kpid
 * Signature: (DDD)Lliba/pid_fuzzy;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_kpid
  (JNIEnv *, jobject, jdouble, jdouble, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    run
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_run
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    pos
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_pos
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    inc
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_liba_pid_1fuzzy_inc
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     liba_pid_fuzzy
 * Method:    zero
 * Signature: ()Lliba/pid_fuzzy;
 */
JNIEXPORT jobject JNICALL Java_liba_pid_1fuzzy_zero
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
