#include "a/host/a.h"
#include <emscripten/bind.h>

#include "a/pid.h"

class pid: public a_pid_s
{
    void init()
    {
        kp = 0;
        ki = 0;
        kd = 0;
        a_pid_init(this, 0);
    }

public:
    pid()
    {
        summax = +A_FLOAT_INF;
        outmax = +A_FLOAT_INF;
        outmin = -A_FLOAT_INF;
        mode = A_PID_INC;
        init();
    }
    pid(a_float_t min, a_float_t max)
    {
        summax = +A_FLOAT_INF;
        outmax = max;
        outmin = min;
        mode = A_PID_INC;
        init();
    }
    pid(a_float_t min, a_float_t max, a_float_t sum)
    {
        summax = sum;
        outmax = max;
        outmin = min;
        mode = A_PID_POS;
        init();
    }
    a_float_t get_out() const { return out.f; }
    a_float_t get_fdb() const { return fdb.f; }
    a_float_t get_err() const { return err.f; }
};

#include "a/pid/fuzzy.h"

static emscripten::val concat(emscripten::val x)
{
    emscripten::val array = emscripten::val::array();
    return array["concat"].call<emscripten::val>("apply", array, x);
}

static a_float_t *float_array(emscripten::val const &x, a_size_t n, a_float_t *p)
{
    p = a_float_c(*, a_alloc(p, sizeof(a_float_t) * n));
    a_size_t length = x["length"].as<a_size_t>();
    for (a_size_t i = 0; i < length; ++i)
    {
        p[i] = x[i].as<a_float_t>();
    }
    return p;
}

class pid_fuzzy: public a_pid_fuzzy_s
{
    void init()
    {
        pid.kp = 0;
        pid.ki = 0;
        pid.kd = 0;
        op = a_pid_fuzzy_op(A_PID_FUZZY_EQU);
        kp = 0;
        ki = 0;
        kd = 0;
        order = 0;
        joint = 0;
        me = nullptr;
        mec = nullptr;
        mkp = nullptr;
        mki = nullptr;
        mkd = nullptr;
        idx = nullptr;
        val = nullptr;
        a_pid_fuzzy_init(this, 0);
    }

public:
    pid_fuzzy()
    {
        pid.summax = +A_FLOAT_INF;
        pid.outmax = +A_FLOAT_INF;
        pid.outmin = -A_FLOAT_INF;
        pid.mode = A_PID_INC;
        init();
    }
    pid_fuzzy(a_float_t min, a_float_t max)
    {
        pid.summax = +A_FLOAT_INF;
        pid.outmax = max;
        pid.outmin = min;
        pid.mode = A_PID_INC;
        init();
    }
    pid_fuzzy(a_float_t min, a_float_t max, a_float_t sum)
    {
        pid.summax = sum;
        pid.outmax = max;
        pid.outmin = min;
        pid.mode = A_PID_POS;
        init();
    }
    ~pid_fuzzy()
    {
        union
        {
            a_float_t const *p;
            a_float_t *o;
        } u;
        a_alloc(idx, 0);
        u.p = me;
        a_alloc(u.o, 0);
        u.p = mec;
        a_alloc(u.o, 0);
        u.p = mkp;
        a_alloc(u.o, 0);
        u.p = mki;
        a_alloc(u.o, 0);
        u.p = mkd;
        a_alloc(u.o, 0);
    }
    a_float_t get_summax() const { return pid.summax; }
    void set_summax(a_float_t summax) { pid.summax = summax; }
    a_float_t get_outmax() const { return pid.outmax; }
    void set_outmax(a_float_t outmax) { pid.outmax = outmax; }
    a_float_t get_outmin() const { return pid.outmin; }
    void set_outmin(a_float_t outmin) { pid.outmin = outmin; }
    a_float_t get_out() const { return pid.out.f; }
    a_float_t get_fdb() const { return pid.fdb.f; }
    a_float_t get_err() const { return pid.err.f; }
    unsigned int get_mode() const { return pid.mode; }
    void set_mode(unsigned int mode) { pid.mode = mode; }
};

#include "a/pid/neuron.h"

class pid_neuron: public a_pid_neuron_s
{
    void init()
    {
        pid.kp = 0;
        pid.ki = 0;
        pid.kd = 0;
        wp.f = 1;
        wi.f = 0;
        wd.f = 0;
        k = 1;
        a_pid_neuron_init(this, 0);
    }

public:
    pid_neuron()
    {
        pid.summax = +A_FLOAT_INF;
        pid.outmax = +A_FLOAT_INF;
        pid.outmin = -A_FLOAT_INF;
        pid.mode = A_PID_INC;
        init();
    }
    pid_neuron(a_float_t min, a_float_t max)
    {
        pid.summax = +A_FLOAT_INF;
        pid.outmax = max;
        pid.outmin = min;
        pid.mode = A_PID_INC;
        init();
    }
    a_float_t get_kp() const { return pid.kp; }
    void set_kp(a_float_t kp) { pid.kp = kp; }
    a_float_t get_ki() const { return pid.ki; }
    void set_ki(a_float_t ki) { pid.ki = ki; }
    a_float_t get_kd() const { return pid.kd; }
    void set_kd(a_float_t kd) { pid.kd = kd; }
    a_float_t get_wp() const { return wp.f; }
    void set_wp(a_float_t _wp) { wp.f = _wp; }
    a_float_t get_wi() const { return wi.f; }
    void set_wi(a_float_t _wi) { wi.f = _wi; }
    a_float_t get_wd() const { return wd.f; }
    void set_wd(a_float_t _wd) { wd.f = _wd; }
    a_float_t get_summax() const { return pid.summax; }
    void set_summax(a_float_t summax) { pid.summax = summax; }
    a_float_t get_outmax() const { return pid.outmax; }
    void set_outmax(a_float_t outmax) { pid.outmax = outmax; }
    a_float_t get_outmin() const { return pid.outmin; }
    void set_outmin(a_float_t outmin) { pid.outmin = outmin; }
    a_float_t get_out() const { return pid.out.f; }
    a_float_t get_fdb() const { return pid.fdb.f; }
    a_float_t get_err() const { return pid.err.f; }
    a_float_t get_ec() const { return ec.f; }
    unsigned int get_mode() const { return pid.mode; }
    void set_mode(unsigned int mode) { pid.mode = mode; }
};

#include "a/polytrack.h"

class polytrack3: public a_polytrack3_s
{
public:
    polytrack3(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
               a_float_t v0 = 0, a_float_t v1 = 0)
    {
        a_polytrack3_gen(this, t0, t1, q0, q1, v0, v1);
    }
    emscripten::val get_k() const
    {
        return emscripten::val(emscripten::typed_memory_view(A_LEN(k), k));
    }
};

class polytrack5: public a_polytrack5_s
{
public:
    polytrack5(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
               a_float_t v0 = 0, a_float_t v1 = 0,
               a_float_t a0 = 0, a_float_t a1 = 0)
    {
        a_polytrack5_gen(this, t0, t1, q0, q1, v0, v1, a0, a1);
    }
    emscripten::val get_k() const
    {
        return emscripten::val(emscripten::typed_memory_view(A_LEN(k), k));
    }
};

class polytrack7: public a_polytrack7_s
{
public:
    polytrack7(a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1,
               a_float_t v0 = 0, a_float_t v1 = 0,
               a_float_t a0 = 0, a_float_t a1 = 0,
               a_float_t j0 = 0, a_float_t j1 = 0)
    {
        a_polytrack7_gen(this, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    }
    emscripten::val get_k() const
    {
        return emscripten::val(emscripten::typed_memory_view(A_LEN(k), k));
    }
};

#include "a/tf.h"

class tf: public a_tf_s
{
    void set_num_(emscripten::val const &_num, a_float_t *num)
    {
        a_uint_t num_n = _num["length"].as<a_uint_t>();
        a_float_t *p = float_array(_num, a_size_c(, num_n) * 2, num);
        a_tf_set_num(this, num_n, p, p + num_n);
    }
    void set_den_(emscripten::val const &_den, a_float_t *den)
    {
        a_uint_t den_n = _den["length"].as<a_uint_t>();
        a_float_t *p = float_array(_den, a_size_c(, den_n) * 2, den);
        a_tf_set_den(this, den_n, p, p + den_n);
    }

public:
    tf(emscripten::val const &num, emscripten::val const &den)
    {
        set_num_(num, nullptr);
        set_den_(den, nullptr);
    }
    ~tf()
    {
        union
        {
            a_float_t const *p;
            a_float_t *o;
        } u;
        u.p = num_p;
        a_alloc(u.o, 0);
        u.p = den_p;
        a_alloc(u.o, 0);
    }
    emscripten::val get_input() const
    {
        return emscripten::val(emscripten::typed_memory_view(num_n, input));
    }
    emscripten::val get_output() const
    {
        return emscripten::val(emscripten::typed_memory_view(den_n, output));
    }
    emscripten::val get_num() const
    {
        return emscripten::val(emscripten::typed_memory_view(num_n, num_p));
    }
    tf *set_num(emscripten::val const &num)
    {
        union
        {
            a_float_t const *p;
            a_float_t *o;
        } u = {num_p};
        set_num_(num, u.o);
        return this;
    }
    emscripten::val get_den() const
    {
        return emscripten::val(emscripten::typed_memory_view(den_n, den_p));
    }
    tf *set_den(emscripten::val const &den)
    {
        union
        {
            a_float_t const *p;
            a_float_t *o;
        } u = {den_p};
        set_den_(den, u.o);
        return this;
    }
};

#include "a/mf.h"
#include "a/math.h"
#include "a/version.h"
#if __has_warning("-Wglobal-constructors")
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif /* -Wglobal-constructors */
EMSCRIPTEN_BINDINGS(liba) // NOLINT
{
    emscripten::function("f32_rsqrt", a_f32_rsqrt);
    emscripten::function("f64_rsqrt", a_f64_rsqrt);
    emscripten::constant("MF_NUL", a_uint_c(, A_MF_NUL));
    emscripten::function("mf_gauss", a_mf_gauss);
    emscripten::constant("MF_GAUSS", a_uint_c(, A_MF_GAUSS));
    emscripten::function("mf_gauss2", a_mf_gauss2);
    emscripten::constant("MF_GAUSS2", a_uint_c(, A_MF_GAUSS2));
    emscripten::function("mf_gbell", a_mf_gbell);
    emscripten::constant("MF_GBELL", a_uint_c(, A_MF_GBELL));
    emscripten::function("mf_sig", a_mf_sig);
    emscripten::constant("MF_SIG", a_uint_c(, A_MF_SIG));
    emscripten::function("mf_dsig", a_mf_dsig);
    emscripten::constant("MF_DSIG", a_uint_c(, A_MF_DSIG));
    emscripten::function("mf_psig", a_mf_psig);
    emscripten::constant("MF_PSIG", a_uint_c(, A_MF_PSIG));
    emscripten::function("mf_trap", a_mf_trap);
    emscripten::constant("MF_TRAP", a_uint_c(, A_MF_TRAP));
    emscripten::function("mf_tri", a_mf_tri);
    emscripten::constant("MF_TRI", a_uint_c(, A_MF_TRI));
    emscripten::function("mf_lins", a_mf_lins);
    emscripten::constant("MF_LINS", a_uint_c(, A_MF_LINS));
    emscripten::function("mf_linz", a_mf_linz);
    emscripten::constant("MF_LINZ", a_uint_c(, A_MF_LINZ));
    emscripten::function("mf_s", a_mf_s);
    emscripten::constant("MF_S", a_uint_c(, A_MF_S));
    emscripten::function("mf_z", a_mf_z);
    emscripten::constant("MF_Z", a_uint_c(, A_MF_Z));
    emscripten::function("mf_pi", a_mf_pi);
    emscripten::constant("MF_PI", a_uint_c(, A_MF_PI));
    emscripten::constant("PID_OFF", a_uint_c(, A_PID_OFF));
    emscripten::constant("PID_POS", a_uint_c(, A_PID_POS));
    emscripten::constant("PID_INC", a_uint_c(, A_PID_INC));
    emscripten::class_<pid>("pid")
        .constructor<>()
        .constructor<a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t>()
        .function("kpid", emscripten::optional_override([](pid *ctx, a_float_t kp, a_float_t ki, a_float_t kd) {
                      a_pid_kpid(reinterpret_cast<a_pid_s *>(ctx), kp, ki, kd);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("iter", emscripten::optional_override([](pid *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_outf(reinterpret_cast<a_pid_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("zero", emscripten::optional_override([](pid *ctx) {
                      a_pid_zero(reinterpret_cast<a_pid_s *>(ctx));
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .property<a_float_t, void>("kp", &pid::kp)
        .property<a_float_t, void>("ki", &pid::ki)
        .property<a_float_t, void>("kd", &pid::kd)
        .property<a_float_t, void>("summax", &pid::summax)
        .property<a_float_t, void>("outmax", &pid::outmax)
        .property<a_float_t, void>("outmin", &pid::outmin)
        .property("out", &pid::get_out)
        .property("fdb", &pid::get_fdb)
        .property("err", &pid::get_err)
        .property<unsigned int, void>("mode", &pid::mode);
    emscripten::constant("PID_FUZZY_CAP", a_uint_c(, A_PID_FUZZY_CAP));
    emscripten::constant("PID_FUZZY_CAP_ALGEBRA", a_uint_c(, A_PID_FUZZY_CAP_ALGEBRA));
    emscripten::constant("PID_FUZZY_CAP_BOUNDED", a_uint_c(, A_PID_FUZZY_CAP_BOUNDED));
    emscripten::constant("PID_FUZZY_CUP", a_uint_c(, A_PID_FUZZY_CUP));
    emscripten::constant("PID_FUZZY_CUP_ALGEBRA", a_uint_c(, A_PID_FUZZY_CUP_ALGEBRA));
    emscripten::constant("PID_FUZZY_CUP_BOUNDED", a_uint_c(, A_PID_FUZZY_CUP_BOUNDED));
    emscripten::constant("PID_FUZZY_EQU", a_uint_c(, A_PID_FUZZY_EQU));
    emscripten::class_<pid_fuzzy>("pid_fuzzy")
        .constructor<>()
        .constructor<a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t>()
        .function("op", emscripten::optional_override([](pid_fuzzy *ctx, unsigned int op) {
                      a_pid_fuzzy_set_op(reinterpret_cast<a_pid_fuzzy_s *>(ctx), op);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("rule", emscripten::optional_override([](pid_fuzzy *ctx, emscripten::val const &me, emscripten::val const &mec, emscripten::val const &mkp, emscripten::val const &mki, emscripten::val const &mkd) {
                      union
                      {
                          a_float_t const *p;
                          a_float_t *o;
                      } u;
                      ctx->order = me["length"].as<unsigned int>();
                      u.p = ctx->me;
                      ctx->me = float_array(concat(me), me["length"].as<a_size_t>(), u.o);
                      u.p = ctx->mec;
                      ctx->mec = float_array(concat(mec), mec["length"].as<a_size_t>(), u.o);
                      u.p = ctx->mkp;
                      ctx->mkp = float_array(concat(mkp), mkp["length"].as<a_size_t>(), u.o);
                      u.p = ctx->mki;
                      ctx->mki = float_array(concat(mki), mki["length"].as<a_size_t>(), u.o);
                      u.p = ctx->mkd;
                      ctx->mkd = float_array(concat(mkd), mkd["length"].as<a_size_t>(), u.o);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("joint", emscripten::optional_override([](pid_fuzzy *ctx, unsigned int num) {
                      a_pid_fuzzy_joint(reinterpret_cast<a_pid_fuzzy_s *>(ctx), a_alloc(ctx->idx, A_PID_FUZZY_JOINT(num)), num);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("kpid", emscripten::optional_override([](pid_fuzzy *ctx, a_float_t kp, a_float_t ki, a_float_t kd) {
                      a_pid_fuzzy_kpid(reinterpret_cast<a_pid_fuzzy_s *>(ctx), kp, ki, kd);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("iter", emscripten::optional_override([](pid_fuzzy *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_fuzzy_outf(reinterpret_cast<a_pid_fuzzy_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("zero", emscripten::optional_override([](pid_fuzzy *ctx) {
                      a_pid_fuzzy_zero(reinterpret_cast<a_pid_fuzzy_s *>(ctx));
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .property("mode", &pid_fuzzy::get_mode, &pid_fuzzy::set_mode)
        .property<a_float_t, void>("kp", &pid_fuzzy::kp)
        .property<a_float_t, void>("ki", &pid_fuzzy::ki)
        .property<a_float_t, void>("kd", &pid_fuzzy::kd)
        .property("summax", &pid_fuzzy::get_summax, &pid_fuzzy::set_summax)
        .property("outmax", &pid_fuzzy::get_outmax, &pid_fuzzy::set_outmax)
        .property("outmin", &pid_fuzzy::get_outmin, &pid_fuzzy::set_outmin)
        .property("out", &pid_fuzzy::get_out)
        .property("fdb", &pid_fuzzy::get_fdb)
        .property("err", &pid_fuzzy::get_err)
        .property<unsigned int const, void>("order", &pid_fuzzy::order);
    emscripten::class_<pid_neuron>("pid_neuron")
        .constructor<>()
        .constructor<a_float_t, a_float_t>()
        .function("kpid", emscripten::optional_override([](pid_neuron *ctx, a_float_t k, a_float_t kp, a_float_t ki, a_float_t kd) {
                      a_pid_neuron_kpid(reinterpret_cast<a_pid_neuron_s *>(ctx), k, kp, ki, kd);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("wpid", emscripten::optional_override([](pid_neuron *ctx, a_float_t wp, a_float_t wi, a_float_t wd) {
                      a_pid_neuron_wpid(reinterpret_cast<a_pid_neuron_s *>(ctx), wp, wi, wd);
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("iter", emscripten::optional_override([](pid_neuron *ctx, a_float_t set, a_float_t fdb) {
                      return a_pid_neuron_outf(reinterpret_cast<a_pid_neuron_s *>(ctx), set, fdb);
                  }),
                  emscripten::allow_raw_pointers())
        .function("zero", emscripten::optional_override([](pid_neuron *ctx) {
                      a_pid_neuron_zero(reinterpret_cast<a_pid_neuron_s *>(ctx));
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .property("mode", &pid_neuron::get_mode, &pid_neuron::set_mode)
        .property<a_float_t, void>("k", &pid_neuron::k)
        .property("kp", &pid_neuron::get_kp, &pid_neuron::set_kp)
        .property("ki", &pid_neuron::get_ki, &pid_neuron::set_ki)
        .property("kd", &pid_neuron::get_kd, &pid_neuron::set_kd)
        .property("wp", &pid_neuron::get_wp, &pid_neuron::set_wp)
        .property("wi", &pid_neuron::get_wi, &pid_neuron::set_wi)
        .property("wd", &pid_neuron::get_wd, &pid_neuron::set_wd)
        .property("summax", &pid_neuron::get_summax, &pid_neuron::set_summax)
        .property("outmax", &pid_neuron::get_outmax, &pid_neuron::set_outmax)
        .property("outmin", &pid_neuron::get_outmin, &pid_neuron::set_outmin)
        .property("out", &pid_neuron::get_out)
        .property("fdb", &pid_neuron::get_fdb)
        .property("err", &pid_neuron::get_err)
        .property("ec", &pid_neuron::get_ec);
    emscripten::class_<polytrack3>("polytrack3")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", emscripten::optional_override([](polytrack3 *ctx, a_float_t dt) {
                      return a_polytrack3_pos(reinterpret_cast<polytrack3 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("vel", emscripten::optional_override([](polytrack3 *ctx, a_float_t dt) {
                      return a_polytrack3_vel(reinterpret_cast<polytrack3 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("acc", emscripten::optional_override([](polytrack3 *ctx, a_float_t dt) {
                      return a_polytrack3_acc(reinterpret_cast<polytrack3 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("out", emscripten::optional_override([](polytrack3 *ctx, a_float_t dt) {
                      a_float_t out[3];
                      a_polytrack3_out(reinterpret_cast<polytrack3 *>(ctx), dt, out);
                      return emscripten::val(emscripten::typed_memory_view(A_LEN(out), out));
                  }),
                  emscripten::allow_raw_pointers())
        .property("k", &polytrack3::get_k);
    emscripten::class_<polytrack5>("polytrack5")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", emscripten::optional_override([](polytrack5 *ctx, a_float_t dt) {
                      return a_polytrack5_pos(reinterpret_cast<polytrack5 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("vel", emscripten::optional_override([](polytrack5 *ctx, a_float_t dt) {
                      return a_polytrack5_vel(reinterpret_cast<polytrack5 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("acc", emscripten::optional_override([](polytrack5 *ctx, a_float_t dt) {
                      return a_polytrack5_acc(reinterpret_cast<polytrack5 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("out", emscripten::optional_override([](polytrack5 *ctx, a_float_t dt) {
                      a_float_t out[3];
                      a_polytrack5_out(reinterpret_cast<polytrack5 *>(ctx), dt, out);
                      return emscripten::val(emscripten::typed_memory_view(A_LEN(out), out));
                  }),
                  emscripten::allow_raw_pointers())
        .property("k", &polytrack5::get_k);
    emscripten::class_<polytrack7>("polytrack7")
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .constructor<a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t, a_float_t>()
        .function("pos", emscripten::optional_override([](polytrack7 *ctx, a_float_t dt) {
                      return a_polytrack7_pos(reinterpret_cast<polytrack7 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("vel", emscripten::optional_override([](polytrack7 *ctx, a_float_t dt) {
                      return a_polytrack7_vel(reinterpret_cast<polytrack7 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("acc", emscripten::optional_override([](polytrack7 *ctx, a_float_t dt) {
                      return a_polytrack7_acc(reinterpret_cast<polytrack7 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("jer", emscripten::optional_override([](polytrack7 *ctx, a_float_t dt) {
                      return a_polytrack7_jer(reinterpret_cast<polytrack7 *>(ctx), dt);
                  }),
                  emscripten::allow_raw_pointers())
        .function("out", emscripten::optional_override([](polytrack7 *ctx, a_float_t dt) {
                      a_float_t out[4];
                      a_polytrack7_out(reinterpret_cast<polytrack7 *>(ctx), dt, out);
                      return emscripten::val(emscripten::typed_memory_view(A_LEN(out), out));
                  }),
                  emscripten::allow_raw_pointers())
        .property("k", &polytrack7::get_k);
    emscripten::class_<tf>("tf")
        .constructor<emscripten::val, emscripten::val>()
        .function("iter", emscripten::optional_override([](tf *ctx, a_float_t x) {
                      return a_tf_iter(reinterpret_cast<a_tf_s *>(ctx), x);
                  }),
                  emscripten::allow_raw_pointers())
        .function("zero", emscripten::optional_override([](tf *ctx) {
                      a_tf_zero(reinterpret_cast<a_tf_s *>(ctx));
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("set_num", &tf::set_num, emscripten::allow_raw_pointers())
        .function("set_den", &tf::set_den, emscripten::allow_raw_pointers())
        .property("input", &tf::get_input)
        .property("output", &tf::get_output)
        .property("num", &tf::get_num, &tf::set_num)
        .property("den", &tf::get_den, &tf::set_den);
    emscripten::class_<a::version>("version")
        .constructor<>()
        .constructor<a_uint_t>()
        .constructor<a_uint_t, a_uint_t>()
        .constructor<a_uint_t, a_uint_t, a_uint_t>()
        .property<unsigned int, void>("major", &a::version::major)
        .property<unsigned int, void>("minor", &a::version::minor)
        .property<unsigned int, void>("patch", &a::version::patch)
        .function("toString", emscripten::optional_override([](a::version const *ctx) {
                      return std::to_string(ctx->major) + "." + std::to_string(ctx->minor) + "." + std::to_string(ctx->patch);
                  }),
                  emscripten::allow_raw_pointers())
        .function("parse", emscripten::optional_override([](a::version *ctx, std::string const &ver) {
                      a_version_parse(ctx, ver.c_str());
                      return ctx;
                  }),
                  emscripten::allow_raw_pointers())
        .function("lt", &a::version::operator<)
        .function("gt", &a::version::operator>)
        .function("le", &a::version::operator<=)
        .function("ge", &a::version::operator>=)
        .function("eq", &a::version::operator==)
        .function("ne", &a::version::operator!=)
        .function("cmp", &a_version_cmp, emscripten::allow_raw_pointers());
    emscripten::constant("VERSION_TWEAK", std::to_string(A_VERSION_TWEAK));
    emscripten::constant("VERSION_PATCH", A_VERSION_PATCH);
    emscripten::constant("VERSION_MINOR", A_VERSION_MINOR);
    emscripten::constant("VERSION_MAJOR", A_VERSION_MAJOR);
    emscripten::constant("VERSION", std::string{A_VERSION});
    emscripten::function("version_check", &a_version_check);
}
