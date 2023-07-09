#include "pid_fuzzy.h"
#include "liba_pid_fuzzy.h"

j_pid_fuzzy_s *j_pid_fuzzy_new(JNIEnv *const jenv, jobject const jobj, j_pid_fuzzy_s *const jctx)
{
    jclass jcls = (*jenv)->FindClass(jenv, CLASSPATH "pid_fuzzy");
    jfieldID pid = (*jenv)->GetFieldID(jenv, jcls, "pid", "L" CLASSPATH "pid;");
    j_pid_new(jenv, (*jenv)->GetObjectField(jenv, jobj, pid), &jctx->pid);
    jctx->me = (*jenv)->GetFieldID(jenv, jcls, "me", "[D");
    jctx->jme = (*jenv)->GetObjectField(jenv, jobj, jctx->me);
    jctx->mec = (*jenv)->GetFieldID(jenv, jcls, "mec", "[D");
    jctx->jmec = (*jenv)->GetObjectField(jenv, jobj, jctx->mec);
    jctx->mkp = (*jenv)->GetFieldID(jenv, jcls, "mkp", "[D");
    jctx->jmkp = (*jenv)->GetObjectField(jenv, jobj, jctx->mkp);
    jctx->mki = (*jenv)->GetFieldID(jenv, jcls, "mki", "[D");
    jctx->jmki = (*jenv)->GetObjectField(jenv, jobj, jctx->mki);
    jctx->mkd = (*jenv)->GetFieldID(jenv, jcls, "mkd", "[D");
    jctx->jmkd = (*jenv)->GetObjectField(jenv, jobj, jctx->mkd);
    jctx->idx = (*jenv)->GetFieldID(jenv, jcls, "idx", "[I");
    jctx->jidx = (*jenv)->GetObjectField(jenv, jobj, jctx->idx);
    jctx->val = (*jenv)->GetFieldID(jenv, jcls, "val", "[D");
    jctx->jval = (*jenv)->GetObjectField(jenv, jobj, jctx->val);
    jctx->op = (*jenv)->GetFieldID(jenv, jcls, "op", "J");
    jctx->kp = (*jenv)->GetFieldID(jenv, jcls, "kp", "D");
    jctx->ki = (*jenv)->GetFieldID(jenv, jcls, "ki", "D");
    jctx->kd = (*jenv)->GetFieldID(jenv, jcls, "kd", "D");
    jctx->jenv = jenv;
    jctx->jobj = jobj;
    return jctx;
}

jobject j_pid_fuzzy_get(j_pid_fuzzy_s const *const jctx, a_pid_fuzzy_s *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    j_pid_get(&jctx->pid, &ctx->pid);
    ctx->me = NULL;
    if (jctx->jme)
    {
        ctx->me = (*jenv)->GetDoubleArrayElements(jenv, jctx->jme, NULL);
    }
    ctx->mec = NULL;
    if (jctx->jmec)
    {
        ctx->mec = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmec, NULL);
    }
    ctx->mkp = NULL;
    if (jctx->jmkp)
    {
        ctx->mkp = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmkp, NULL);
    }
    ctx->mki = NULL;
    if (jctx->jmki)
    {
        ctx->mki = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmki, NULL);
    }
    ctx->mkd = NULL;
    if (jctx->jmkd)
    {
        ctx->mkd = (*jenv)->GetDoubleArrayElements(jenv, jctx->jmkd, NULL);
    }
    ctx->idx = NULL;
    if (jctx->jidx)
    {
        ctx->idx = (unsigned int *)(*jenv)->GetIntArrayElements(jenv, jctx->jidx, NULL);
    }
    ctx->val = NULL;
    if (jctx->jval)
    {
        ctx->val = (*jenv)->GetDoubleArrayElements(jenv, jctx->jval, NULL);
    }
    jlong op = (*jenv)->GetLongField(jenv, jobj, jctx->op);
    ctx->op = (a_float_t(*)(a_float_t, a_float_t))(intptr_t)op; // NOLINT(performance-no-int-to-ptr)
    ctx->kp = (*jenv)->GetDoubleField(jenv, jobj, jctx->kp);
    ctx->ki = (*jenv)->GetDoubleField(jenv, jobj, jctx->ki);
    ctx->kd = (*jenv)->GetDoubleField(jenv, jobj, jctx->kd);
    return jctx->jobj;
}

jobject j_pid_fuzzy_set(j_pid_fuzzy_s const *const jctx, a_pid_fuzzy_s const *const ctx)
{
    JNIEnv *jenv = jctx->jenv;
    jobject jobj = jctx->jobj;
    j_pid_set(&jctx->pid, &ctx->pid);
    if (ctx->me)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *me = (jdouble *)(intptr_t)ctx->me;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmec, me, JNI_ABORT);
    }
    if (ctx->mec)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *mec = (jdouble *)(intptr_t)ctx->mec;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmec, mec, JNI_ABORT);
    }
    if (ctx->mkp)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *mkp = (jdouble *)(intptr_t)ctx->mkp;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmkp, mkp, JNI_ABORT);
    }
    if (ctx->mki)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *mki = (jdouble *)(intptr_t)ctx->mki;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmki, mki, JNI_ABORT);
    }
    if (ctx->mkd)
    {
        // NOLINTNEXTLINE(performance-no-int-to-ptr)
        jdouble *mkd = (jdouble *)(intptr_t)ctx->mkd;
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jmkd, mkd, JNI_ABORT);
    }
    if (ctx->idx)
    {
        (*jenv)->ReleaseIntArrayElements(jenv, jctx->jidx, (jint *)ctx->idx, JNI_ABORT);
    }
    if (ctx->val)
    {
        (*jenv)->ReleaseDoubleArrayElements(jenv, jctx->jval, ctx->val, JNI_ABORT);
    }
    (*jenv)->SetLongField(jenv, jobj, jctx->op, (intptr_t)ctx->op);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->kp, ctx->kp);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->ki, ctx->ki);
    (*jenv)->SetDoubleField(jenv, jobj, jctx->kd, ctx->kd);
    return jctx->jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_inc)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_get(j_pid_fuzzy_new(jenv, jobj, &jctx), &ctx);
    a_pid_fuzzy_inc(&ctx);
    return j_pid_fuzzy_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_off)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_get(j_pid_fuzzy_new(jenv, jobj, &jctx), &ctx);
    a_pid_fuzzy_off(&ctx);
    return j_pid_fuzzy_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_pos)(JNIEnv *jenv, jobject jobj, jdouble jmax)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_get(j_pid_fuzzy_new(jenv, jobj, &jctx), &ctx);
    a_pid_fuzzy_pos(&ctx, jmax);
    return j_pid_fuzzy_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_mode)(JNIEnv *jenv, jobject jobj, jint jmode)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_get(j_pid_fuzzy_new(jenv, jobj, &jctx), &ctx);
    a_pid_set_mode(&ctx.pid, (unsigned int)jmode);
    return j_pid_fuzzy_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_time)(JNIEnv *jenv, jobject jobj, jdouble jdt)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_get(j_pid_fuzzy_new(jenv, jobj, &jctx), &ctx);
    a_pid_set_dt(&ctx.pid, jdt);
    return j_pid_fuzzy_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_kpid)(JNIEnv *jenv, jobject jobj, jdouble jkp, jdouble jki, jdouble jkd)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_get(j_pid_fuzzy_new(jenv, jobj, &jctx), &ctx);
    a_pid_fuzzy_kpid(&ctx, jkp, jki, jkd);
    return j_pid_fuzzy_set(&jctx, &ctx);
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_buff)(JNIEnv *jenv, jobject jobj, jint jnum)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_new(jenv, jobj, &jctx);
    j_pid_get(&jctx.pid, &ctx.pid);
    (*jenv)->SetObjectField(jenv, jobj, jctx.idx, (*jenv)->NewIntArray(jenv, A_PID_FUZZY_IDX(jnum)));
    (*jenv)->SetObjectField(jenv, jobj, jctx.val, (*jenv)->NewDoubleArray(jenv, A_PID_FUZZY_VAL(jnum)));
    a_pid_fuzzy_set_bufnum(&ctx, (unsigned int)jnum);
    j_pid_set(&jctx.pid, &ctx.pid);
    return jobj;
}

static jobject concat(j_pid_fuzzy_s const *jctx, jobjectArray jval)
{
    jsize length = 0;
    JNIEnv *jenv = jctx->jenv;
    jsize num = (*jenv)->GetArrayLength(jenv, jval);
    for (jsize idx = 0; idx != num; ++idx)
    {
        length += (*jenv)->GetArrayLength(jenv, (*jenv)->GetObjectArrayElement(jenv, jval, idx));
    }
    jobject obj = (*jenv)->NewDoubleArray(jenv, length);
    jdouble *val = (*jenv)->GetDoubleArrayElements(jenv, obj, NULL), *jptr = val;
    for (jsize idx = 0, jnum = 0; idx != num; ++idx, jptr += jnum)
    {
        jobject jobj = (*jenv)->GetObjectArrayElement(jenv, jval, idx);
        jnum = (*jenv)->GetArrayLength(jenv, jobj);
        (*jenv)->GetDoubleArrayRegion(jenv, jobj, 0, jnum, jptr);
    }
    (*jenv)->ReleaseDoubleArrayElements(jenv, obj, val, 0);
    return obj;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_rule)(JNIEnv *jenv, jobject jobj, jobjectArray jme, jobjectArray jmec,
                                                    jobjectArray jmkp, jobjectArray jmki, jobjectArray jmkd)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_new(jenv, jobj, &jctx);
    j_pid_get(&jctx.pid, &ctx.pid);
    (*jenv)->SetObjectField(jenv, jobj, jctx.me, concat(&jctx, jme));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mec, concat(&jctx, jmec));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mkp, concat(&jctx, jmkp));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mki, concat(&jctx, jmki));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mkd, concat(&jctx, jmkd));
    a_pid_fuzzy_set_col(&ctx, (unsigned int)(*jenv)->GetArrayLength(jenv, jmkp));
    j_pid_set(&jctx.pid, &ctx.pid);
    return jobj;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_init)(JNIEnv *jenv, jobject jobj, jdouble jdt, jobjectArray jme, jobjectArray jmec,
                                                    jobjectArray jmkp, jobjectArray jmki, jobjectArray jmkd, jdouble jmin, jdouble jmax)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    unsigned int col = (unsigned int)(*jenv)->GetArrayLength(jenv, jmkp);
    j_pid_fuzzy_new(jenv, jobj, &jctx);
    (*jenv)->SetObjectField(jenv, jobj, jctx.me, concat(&jctx, jme));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mec, concat(&jctx, jmec));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mkp, concat(&jctx, jmkp));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mki, concat(&jctx, jmki));
    (*jenv)->SetObjectField(jenv, jobj, jctx.mkd, concat(&jctx, jmkd));
    a_pid_fuzzy_init(&ctx, jdt, col, 0, 0, 0, 0, 0, jmin, jmax);
    return j_pid_fuzzy_set(&jctx, &ctx);
}

JNIEXPORT jdouble JNICALL JPACKAGE(pid_1fuzzy_iter)(JNIEnv *jenv, jobject jobj, jdouble jset, jdouble jfdb)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_get(j_pid_fuzzy_new(jenv, jobj, &jctx), &ctx);
    jdouble jres = a_pid_fuzzy_outf(&ctx, jset, jfdb);
    j_pid_fuzzy_set(&jctx, &ctx);
    return jres;
}

JNIEXPORT jobject JNICALL JPACKAGE(pid_1fuzzy_zero)(JNIEnv *jenv, jobject jobj)
{
    a_pid_fuzzy_s ctx;
    j_pid_fuzzy_s jctx;
    j_pid_fuzzy_get(j_pid_fuzzy_new(jenv, jobj, &jctx), &ctx);
    a_pid_fuzzy_zero(&ctx);
    return j_pid_fuzzy_set(&jctx, &ctx);
}
