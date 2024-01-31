#include "a.h"
#include "a/polytraj5.h"

static JSClassID liba_polytraj5_class_id;

static void liba_polytraj5_finalizer(JSRuntime *rt, JSValue val)
{
    js_free_rt(rt, JS_GetOpaque(val, liba_polytraj5_class_id));
}

static JSClassDef liba_polytraj5_class = {"polytraj5", .finalizer = liba_polytraj5_finalizer};

static JSValue liba_polytraj5_ctor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto, clazz = JS_UNDEFINED;
    a_polytraj5 *const self = (a_polytraj5 *)js_mallocz(ctx, sizeof(a_polytraj5));
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < 3; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { goto fail; }
    }
    for (int i = 3; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { goto fail; }
    }
    a_polytraj5_gen(self, (a_float)args[0],
                    (a_float)args[1], (a_float)args[2],
                    (a_float)args[3], (a_float)args[4],
                    (a_float)args[5], (a_float)args[6]);
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto)) { goto fail; }
    clazz = JS_NewObjectProtoClass(ctx, proto, liba_polytraj5_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(clazz)) { goto fail; }
    JS_SetOpaque(clazz, self);
    return clazz;
fail:
    js_free(ctx, self);
    JS_FreeValue(ctx, clazz);
    return JS_EXCEPTION;
}

static JSValue liba_polytraj5_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    a_polytraj5 *const self = (a_polytraj5 *)JS_GetOpaque2(ctx, this_val, liba_polytraj5_class_id);
    if (!self) { return JS_EXCEPTION; }
    switch (magic)
    {
    case 0: return js_array_num_new(ctx, self->q, A_LEN(self->q));
    case 1: return js_array_num_new(ctx, self->v, A_LEN(self->v));
    case 2: return js_array_num_new(ctx, self->a, A_LEN(self->a));
    default: return JS_UNDEFINED;
    }
}

static JSValue liba_polytraj5_gen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    a_polytraj5 *const self = (a_polytraj5 *)JS_GetOpaque2(ctx, this_val, liba_polytraj5_class_id);
    if (!self) { return JS_EXCEPTION; }
    double args[] = {0, 0, 0, 0, 0, 0, 0};
    if (argc > (int)A_LEN(args)) { argc = (int)A_LEN(args); }
    for (int i = 0; i < 3; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    for (int i = 3; i < argc; ++i)
    {
        if (JS_ToFloat64(ctx, &args[i], argv[i])) { return JS_EXCEPTION; }
    }
    a_polytraj5_gen(self, (a_float)args[0],
                    (a_float)args[1], (a_float)args[2],
                    (a_float)args[3], (a_float)args[4],
                    (a_float)args[5], (a_float)args[6]);
    return JS_UNDEFINED;
}

static JSValue liba_polytraj5_pos(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_polytraj5 *const self = (a_polytraj5 *)JS_GetOpaque2(ctx, this_val, liba_polytraj5_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float pos = a_polytraj5_pos(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)pos);
}

static JSValue liba_polytraj5_vel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_polytraj5 *const self = (a_polytraj5 *)JS_GetOpaque2(ctx, this_val, liba_polytraj5_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float vel = a_polytraj5_vel(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)vel);
}

static JSValue liba_polytraj5_acc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    (void)argc;
    a_polytraj5 *const self = (a_polytraj5 *)JS_GetOpaque2(ctx, this_val, liba_polytraj5_class_id);
    if (!self) { return JS_EXCEPTION; }
    double dt;
    if (JS_ToFloat64(ctx, &dt, argv[0])) { return JS_EXCEPTION; }
    a_float acc = a_polytraj5_acc(self, (a_float)dt);
    return JS_NewFloat64(ctx, (double)acc);
}

static JSCFunctionListEntry const liba_polytraj5_proto[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "a.polytraj5", 0),
    JS_CGETSET_MAGIC_DEF("q", liba_polytraj5_get, NULL, 0),
    JS_CGETSET_MAGIC_DEF("v", liba_polytraj5_get, NULL, 1),
    JS_CGETSET_MAGIC_DEF("a", liba_polytraj5_get, NULL, 2),
    JS_CFUNC_DEF("gen", 7, liba_polytraj5_gen),
    JS_CFUNC_DEF("pos", 1, liba_polytraj5_pos),
    JS_CFUNC_DEF("vel", 1, liba_polytraj5_vel),
    JS_CFUNC_DEF("acc", 1, liba_polytraj5_acc),
};

int js_liba_polytraj5_init(JSContext *ctx, JSModuleDef *m)
{
    JS_NewClassID(&liba_polytraj5_class_id);
    JS_NewClass(JS_GetRuntime(ctx), liba_polytraj5_class_id, &liba_polytraj5_class);

    JSValue const proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, liba_polytraj5_proto, A_LEN(liba_polytraj5_proto));

    JSValue const clazz = JS_NewCFunction2(ctx, liba_polytraj5_ctor, "polytraj5", 7, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, clazz, proto);
    JS_SetClassProto(ctx, liba_polytraj5_class_id, proto);

    return JS_SetModuleExport(ctx, m, "polytraj5", clazz);
}
