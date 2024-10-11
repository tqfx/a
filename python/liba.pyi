from typing import TypeVar, Iterable, Sequence, SupportsIndex, overload

_T = TypeVar("_T", int, float)

class memoryview(Iterable[_T]):  # built in cython
    def __len__(self) -> int: ...
    def is_c_contig(self) -> bool: ...
    def is_f_contig(self) -> bool: ...
    def copy(self) -> memoryview[_T]: ...
    def copy_fortran(self) -> memoryview[_T]: ...
    @overload
    def __getitem__(self, key: SupportsIndex, /) -> _T: ...
    @overload
    def __getitem__(self, key: slice, /) -> array[_T]: ...
    @overload
    def __setitem__(self, key: SupportsIndex, value: _T, /) -> None: ...
    @overload
    def __setitem__(self, key: slice, value: array[_T], /) -> None: ...
    def __delitem__(self, key: SupportsIndex | slice, /) -> None: ...
    @property
    def T(self) -> memoryview[_T]: ...
    @property
    def base(self) -> array[_T]: ...
    @property
    def itemsize(self) -> int: ...
    @property
    def nbytes(self) -> int: ...
    @property
    def ndim(self) -> int: ...
    @property
    def shape(self) -> tuple[int]: ...
    @property
    def size(self) -> int: ...
    @property
    def strides(self) -> tuple[int]: ...
    @property
    def suboffsets(self) -> tuple[int]: ...

class array(Sequence[_T]):  # built in cython
    def __len__(self) -> int: ...
    def is_c_contig(self) -> bool: ...
    def is_f_contig(self) -> bool: ...
    def copy(self) -> memoryview[_T]: ...
    def copy_fortran(self) -> memoryview[_T]: ...
    @overload
    def __getitem__(self, key: SupportsIndex, /) -> _T: ...
    @overload
    def __getitem__(self, key: slice, /) -> array[_T]: ...
    @overload
    def __setitem__(self, key: SupportsIndex, value: _T, /) -> None: ...
    @overload
    def __setitem__(self, key: slice, value: array[_T], /) -> None: ...
    def __delitem__(self, key: SupportsIndex | slice, /) -> None: ...
    @property
    def memview(self) -> memoryview[_T]: ...
    @property
    def T(self) -> memoryview[_T]: ...
    @property
    def base(self) -> array[_T]: ...
    @property
    def itemsize(self) -> int: ...
    @property
    def nbytes(self) -> int: ...
    @property
    def ndim(self) -> int: ...
    @property
    def shape(self) -> tuple[int]: ...
    @property
    def size(self) -> int: ...
    @property
    def strides(self) -> tuple[int]: ...
    @property
    def suboffsets(self) -> tuple[int]: ...

def isqrt(x: int) -> int: ...
@overload
def new_u32(x: Iterable[int]) -> array[int]: ...
@overload
def new_u32(x: int) -> array[int]: ...
@overload
def new_u64(x: Iterable[int]) -> array[int]: ...
@overload
def new_u64(x: int) -> array[int]: ...
@overload
def new_f32(x: Iterable[float]) -> array[float]: ...
@overload
def new_f32(x: int) -> array[float]: ...
@overload
def new_f64(x: Iterable[float]) -> array[float]: ...
@overload
def new_f64(x: int) -> array[float]: ...
@overload
def new_float(x: Iterable[float]) -> array[float]: ...
@overload
def new_float(x: int) -> array[float]: ...
@overload
def sqrt_u32(x: Iterable[int]) -> array[int]: ...
@overload
def sqrt_u32(x: int) -> int: ...
@overload
def sqrt_u64(x: Iterable[int]) -> array[int]: ...
@overload
def sqrt_u64(x: int) -> int: ...
@overload
def rsqrt_f32(x: Iterable[float]) -> array[float]: ...
@overload
def rsqrt_f32(x: float) -> float: ...
@overload
def rsqrt_f64(x: Iterable[float]) -> array[float]: ...
@overload
def rsqrt_f64(x: float) -> float: ...
def float_sum(x: Iterable[float]) -> float: ...
def float_sum1(x: Iterable[float]) -> float: ...
def float_sum2(x: Iterable[float]) -> float: ...
def float_mean(x: Iterable[float]) -> float: ...
def hash_bkdr(str: bytes | str, val: int = 0) -> int: ...
def hash_sdbm(str: bytes | str, val: int = 0) -> int: ...

class crc8:
    def __init__(self, poly: int, reversed=False) -> None: ...
    def gen(self, poly: int, reversed=False) -> crc8: ...
    def __call__(self, block: bytes, value=0) -> int: ...
    def pack(self, block: bytes, value=0) -> bytes: ...
    @property
    def table(self) -> array[int]: ...

class crc16:
    def __init__(self, poly: int, reversed=False) -> None: ...
    def gen(self, poly: int, reversed=False) -> crc16: ...
    def __call__(self, block: bytes, value=0) -> int: ...
    def pack(self, block: bytes, value=0) -> bytes: ...
    @property
    def table(self) -> array[int]: ...

class crc32:
    def __init__(self, poly: int, reversed=False) -> None: ...
    def gen(self, poly: int, reversed=False) -> crc32: ...
    def __call__(self, block: bytes, value=0) -> int: ...
    def pack(self, block: bytes, value=0) -> bytes: ...
    @property
    def table(self) -> array[int]: ...

class crc64:
    def __init__(self, poly: int, reversed=False) -> None: ...
    def gen(self, poly: int, reversed=False) -> crc64: ...
    def __call__(self, block: bytes, value=0) -> int: ...
    def pack(self, block: bytes, value=0) -> bytes: ...
    @property
    def table(self) -> array[int]: ...

class hpf:
    def __init__(self, fc: float, ts: float) -> None: ...
    def gen(self, fc: float, ts: float) -> hpf: ...
    def __call__(self, x: float) -> float: ...
    def zero(self) -> hpf: ...
    @property
    def alpha(self) -> float: ...
    @alpha.setter
    def alpha(self, x: float) -> None: ...
    @property
    def output(self) -> float: ...
    @property
    def input(self) -> float: ...

class lpf:
    def __init__(self, fc: float, ts: float) -> None: ...
    def gen(self, fc: float, ts: float) -> lpf: ...
    def __call__(self, x: float) -> float: ...
    def zero(self) -> lpf: ...
    @property
    def alpha(self) -> float: ...
    @alpha.setter
    def alpha(self, x: float) -> None: ...
    @property
    def output(self) -> float: ...

class mf:
    NUL: int
    GAUSS: int
    GAUSS2: int
    GBELL: int
    SIG: int
    DSIG: int
    PSIG: int
    TRAP: int
    TRI: int
    LINS: int
    LINZ: int
    S: int
    Z: int
    PI: int
    @overload
    @staticmethod
    def mf(e: int | float, x: Iterable[float], a: Iterable[float]) -> array[float]: ...
    @overload
    @staticmethod
    def mf(e: int | float, x: float, a: Iterable[float]) -> float: ...
    @overload
    @staticmethod
    def gauss(x: Iterable[float], sigma: float, c: float) -> array[float]: ...
    @overload
    @staticmethod
    def gauss(x: float, sigma: float, c: float) -> float: ...
    @overload
    @staticmethod
    def gauss2(
        x: Iterable[float], sigma1: float, c1: float, sigma2: float, c2: float
    ) -> array[float]: ...
    @overload
    @staticmethod
    def gauss2(x: float, sigma1: float, c1: float, sigma2: float, c2: float) -> float: ...
    @overload
    @staticmethod
    def gbell(x: Iterable[float], a: float, b: float, c: float) -> array[float]: ...
    @overload
    @staticmethod
    def gbell(x: float, a: float, b: float, c: float) -> float: ...
    @overload
    @staticmethod
    def sig(x: Iterable[float], a: float, c: float) -> array[float]: ...
    @overload
    @staticmethod
    def sig(x: float, a: float, c: float) -> float: ...
    @overload
    @staticmethod
    def dsig(x: Iterable[float], a1: float, c1: float, a2: float, c2: float) -> array[float]: ...
    @overload
    @staticmethod
    def dsig(x: float, a1: float, c1: float, a2: float, c2: float) -> float: ...
    @overload
    @staticmethod
    def psig(x: Iterable[float], a1: float, c1: float, a2: float, c2: float) -> array[float]: ...
    @overload
    @staticmethod
    def psig(x: float, a1: float, c1: float, a2: float, c2: float) -> float: ...
    @overload
    @staticmethod
    def trap(x: Iterable[float], a: float, b: float, c: float, d: float) -> array[float]: ...
    @overload
    @staticmethod
    def trap(x: float, a: float, b: float, c: float, d: float) -> float: ...
    @overload
    @staticmethod
    def tri(x: Iterable[float], a: float, b: float, c: float) -> array[float]: ...
    @overload
    @staticmethod
    def tri(x: float, a: float, b: float, c: float) -> float: ...
    @overload
    @staticmethod
    def lins(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @overload
    @staticmethod
    def lins(x: float, a: float, b: float) -> float: ...
    @overload
    @staticmethod
    def linz(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @overload
    @staticmethod
    def linz(x: float, a: float, b: float) -> float: ...
    @overload
    @staticmethod
    def s(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @overload
    @staticmethod
    def s(x: float, a: float, b: float) -> float: ...
    @overload
    @staticmethod
    def z(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @overload
    @staticmethod
    def z(x: float, a: float, b: float) -> float: ...
    @overload
    @staticmethod
    def pi(x: Iterable[float], a: float, b: float, c: float, d: float) -> array[float]: ...
    @overload
    @staticmethod
    def pi(x: float, a: float, b: float, c: float, d: float) -> float: ...

class pid:
    def __init__(self) -> None: ...
    def set_kpid(self, kp: float, ki: float, kd: float) -> pid: ...
    def run(self, set: float, fdb: float) -> float: ...
    def pos(self, set: float, fdb: float) -> float: ...
    def inc(self, set: float, fdb: float) -> float: ...
    def zero(self) -> pid: ...
    @property
    def kp(self) -> float: ...
    @kp.setter
    def kp(self, kp: float) -> None: ...
    @property
    def ki(self) -> float: ...
    @ki.setter
    def ki(self, ki: float) -> None: ...
    @property
    def kd(self) -> float: ...
    @kd.setter
    def kd(self, kd: float) -> None: ...
    @property
    def summax(self) -> float: ...
    @summax.setter
    def summax(self, summax: float) -> None: ...
    @property
    def summin(self) -> float: ...
    @summin.setter
    def summin(self, summin: float) -> None: ...
    @property
    def sum(self) -> float: ...
    @property
    def outmax(self) -> float: ...
    @outmax.setter
    def outmax(self, outmax: float) -> None: ...
    @property
    def outmin(self) -> float: ...
    @outmin.setter
    def outmin(self, outmin: float) -> None: ...
    @property
    def out(self) -> float: ...
    @property
    def fdb(self) -> float: ...
    @property
    def err(self) -> float: ...

class pid_fuzzy:
    CAP: int
    CAP_ALGEBRA: int
    CAP_BOUNDED: int
    CUP: int
    CUP_ALGEBRA: int
    CUP_BOUNDED: int
    EQU: int
    def __init__(self) -> None: ...
    def set_opr(self, opr: int) -> pid_fuzzy: ...
    def set_nfuzz(self, num: int) -> pid_fuzzy: ...
    def set_rule(
        self,
        me: Iterable[Iterable[float]],
        mec: Iterable[Iterable[float]],
        mkp: Iterable[Iterable[float]],
        mki: Iterable[Iterable[float]],
        mkd: Iterable[Iterable[float]],
    ) -> pid_fuzzy: ...
    def set_kpid(self, kp: float, ki: float, kd: float) -> pid_fuzzy: ...
    def run(self, set: float, fdb: float) -> float: ...
    def pos(self, set: float, fdb: float) -> float: ...
    def inc(self, set: float, fdb: float) -> float: ...
    def zero(self) -> pid_fuzzy: ...
    @property
    def me(self) -> array[float]: ...
    @property
    def mec(self) -> array[float]: ...
    @property
    def mkp(self) -> array[float]: ...
    @property
    def mki(self) -> array[float]: ...
    @property
    def mkd(self) -> array[float]: ...
    @property
    def kp(self) -> float: ...
    @kp.setter
    def kp(self, kp: float) -> None: ...
    @property
    def ki(self) -> float: ...
    @ki.setter
    def ki(self, ki: float) -> None: ...
    @property
    def kd(self) -> float: ...
    @kd.setter
    def kd(self, kd: float) -> None: ...
    @property
    def summax(self) -> float: ...
    @summax.setter
    def summax(self, summax: float) -> None: ...
    @property
    def summin(self) -> float: ...
    @summin.setter
    def summin(self, summin: float) -> None: ...
    @property
    def sum(self) -> float: ...
    @property
    def outmax(self) -> float: ...
    @outmax.setter
    def outmax(self, outmax: float) -> None: ...
    @property
    def outmin(self) -> float: ...
    @outmin.setter
    def outmin(self, outmin: float) -> None: ...
    @property
    def out(self) -> float: ...
    @property
    def fdb(self) -> float: ...
    @property
    def err(self) -> float: ...
    @property
    def nrule(self) -> int: ...
    @property
    def nfuzz(self) -> int: ...
    @nfuzz.setter
    def nfuzz(self, nfuzz: int) -> None: ...

class pid_neuro:
    def __init__(self) -> None: ...
    def set_kpid(self, k: float, kp: float, ki: float, kd: float) -> pid_neuro: ...
    def set_wpid(self, wp: float, wi: float, wd: float) -> pid_neuro: ...
    def run(self, set: float, fdb: float) -> float: ...
    def inc(self, set: float, fdb: float) -> float: ...
    def zero(self) -> pid_neuro: ...
    @property
    def k(self) -> float: ...
    @k.setter
    def k(self, k: float) -> None: ...
    @property
    def kp(self) -> float: ...
    @kp.setter
    def kp(self, kp: float) -> None: ...
    @property
    def ki(self) -> float: ...
    @ki.setter
    def ki(self, ki: float) -> None: ...
    @property
    def kd(self) -> float: ...
    @kd.setter
    def kd(self, kd: float) -> None: ...
    @property
    def wp(self) -> float: ...
    @wp.setter
    def wp(self, wp: float) -> None: ...
    @property
    def wi(self) -> float: ...
    @wi.setter
    def wi(self, wi: float) -> None: ...
    @property
    def wd(self) -> float: ...
    @wd.setter
    def wd(self, wd: float) -> None: ...
    @property
    def outmax(self) -> float: ...
    @outmax.setter
    def outmax(self, outmax: float) -> None: ...
    @property
    def outmin(self) -> float: ...
    @outmin.setter
    def outmin(self, outmin: float) -> None: ...
    @property
    def out(self) -> float: ...
    @property
    def fdb(self) -> float: ...
    @property
    def err(self) -> float: ...
    @property
    def ec(self) -> float: ...

@overload
def poly_eval(x: Iterable[float], a: Iterable[float]) -> array[float]: ...
@overload
def poly_eval(x: float, a: Iterable[float]) -> float: ...
@overload
def poly_evar(x: Iterable[float], a: Iterable[float]) -> array[float]: ...
@overload
def poly_evar(x: float, a: Iterable[float]) -> float: ...

class regress_linear:
    @overload
    def __init__(self, coef: float, bias: float = 0): ...
    @overload
    def __init__(self, coef: Iterable[float], bias: float = 0): ...
    def eval(self, x: Iterable[float]) -> float | array[float]: ...
    def err(self, x: Iterable[float], y: Iterable[float]) -> array[float]: ...
    def gd(self, input: Iterable[float], error: float, alpha: float) -> regress_linear: ...
    def sgd(self, x: Iterable[float], y: Iterable[float], alpha: float) -> regress_linear: ...
    def bgd(self, x: Iterable[float], y: Iterable[float], alpha: float) -> regress_linear: ...
    def mgd(
        self,
        x: Iterable[float],
        y: Iterable[float],
        delta: float,
        lrmax: float,
        lrmin: float,
        lrtim: int = 100,
        epoch: int = 1000,
        batch: int = 10,
    ) -> float: ...
    def zero(self) -> regress_linear: ...
    @property
    def coef(self) -> array[float]: ...
    @overload
    @coef.setter
    def coef(self, coef: float) -> None: ...
    @overload
    @coef.setter
    def coef(self, coef: Iterable[float]) -> None: ...
    @property
    def bias(self) -> float: ...
    @bias.setter
    def bias(self, bias: float) -> None: ...

class regress_simple:
    def __init__(self, coef: float = 1, bias: float = 0): ...
    @overload
    def eval(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def eval(self, x: float) -> float: ...
    @overload
    def evar(self, y: Iterable[float]) -> array[float]: ...
    @overload
    def evar(self, y: float) -> float: ...
    def ols_(
        self, x: Iterable[float], y: Iterable[float], x_mean: float, y_mean: float
    ) -> regress_simple: ...
    def olsx(self, x: Iterable[float], y: Iterable[float], x_mean: float) -> regress_simple: ...
    def olsy(self, x: Iterable[float], y: Iterable[float], y_mean: float) -> regress_simple: ...
    def ols(self, x: Iterable[float], y: Iterable[float]) -> regress_simple: ...
    def zero(self) -> regress_simple: ...
    @property
    def coef(self) -> float: ...
    @coef.setter
    def coef(self, coef: float) -> None: ...
    @property
    def bias(self) -> float: ...
    @bias.setter
    def bias(self, bias: float) -> None: ...

class tf:
    def __init__(self, num: Iterable[float], den: Iterable[float]) -> None: ...
    def __call__(self, x: float) -> float: ...
    @property
    def input(self) -> array[float]: ...
    @property
    def num(self) -> array[float]: ...
    @num.setter
    def num(self, num: Iterable[float]) -> None: ...
    @property
    def output(self) -> array[float]: ...
    @property
    def den(self) -> array[float]: ...
    @den.setter
    def den(self, den: Iterable[float]) -> None: ...
    def zero(self) -> tf: ...

class trajbell:
    def gen(
        self,
        jm: float,
        am: float,
        vm: float,
        p0: float,
        p1: float,
        v0: float = 0,
        v1: float = 0,
    ) -> float: ...
    @overload
    def pos(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, x: float) -> float: ...
    @overload
    def vel(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, x: float) -> float: ...
    @overload
    def acc(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, x: float) -> float: ...
    @overload
    def jer(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def jer(self, x: float) -> float: ...
    @property
    def t(self) -> float: ...
    @property
    def tv(self) -> float: ...
    @property
    def ta(self) -> float: ...
    @property
    def td(self) -> float: ...
    @property
    def taj(self) -> float: ...
    @property
    def tdj(self) -> float: ...
    @property
    def p0(self) -> float: ...
    @property
    def p1(self) -> float: ...
    @property
    def v0(self) -> float: ...
    @property
    def v1(self) -> float: ...
    @property
    def vm(self) -> float: ...
    @property
    def jm(self) -> float: ...
    @property
    def am(self) -> float: ...
    @property
    def dm(self) -> float: ...

class trajpoly3:
    def __init__(
        self,
        ts: float,
        p0: float,
        p1: float,
        v0: float = 0,
        v1: float = 0,
    ) -> None: ...
    def gen(
        self,
        ts: float,
        p0: float,
        p1: float,
        v0: float = 0,
        v1: float = 0,
    ) -> trajpoly3: ...
    @overload
    def pos(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, x: float) -> float: ...
    @overload
    def vel(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, x: float) -> float: ...
    @overload
    def acc(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, x: float) -> float: ...
    @property
    def p(self) -> array[float]: ...
    @property
    def v(self) -> array[float]: ...
    @property
    def a(self) -> array[float]: ...

class trajpoly5:
    def __init__(
        self,
        ts: float,
        p0: float,
        p1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
    ) -> None: ...
    def gen(
        self,
        ts: float,
        p0: float,
        p1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
    ) -> trajpoly5: ...
    @overload
    def pos(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, x: float) -> float: ...
    @overload
    def vel(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, x: float) -> float: ...
    @overload
    def acc(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, x: float) -> float: ...
    @property
    def p(self) -> array[float]: ...
    @property
    def v(self) -> array[float]: ...
    @property
    def a(self) -> array[float]: ...

class trajpoly7:
    def __init__(
        self,
        ts: float,
        p0: float,
        p1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
        j0: float = 0,
        j1: float = 0,
    ) -> None: ...
    def gen(
        self,
        ts: float,
        p0: float,
        p1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
        j0: float = 0,
        j1: float = 0,
    ) -> trajpoly7: ...
    @overload
    def pos(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, x: float) -> float: ...
    @overload
    def vel(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, x: float) -> float: ...
    @overload
    def acc(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, x: float) -> float: ...
    @overload
    def jer(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def jer(self, x: float) -> float: ...
    @property
    def p(self) -> array[float]: ...
    @property
    def v(self) -> array[float]: ...
    @property
    def a(self) -> array[float]: ...
    @property
    def j(self) -> array[float]: ...

class trajtrap:
    def gen(
        self,
        vm: float,
        ac: float,
        de: float,
        p0: float,
        p1: float,
        v0: float = 0,
        v1: float = 0,
    ) -> float: ...
    @overload
    def pos(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, x: float) -> float: ...
    @overload
    def vel(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, x: float) -> float: ...
    @overload
    def acc(self, x: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, x: float) -> float: ...
    @property
    def t(self) -> float: ...
    @property
    def p0(self) -> float: ...
    @property
    def p1(self) -> float: ...
    @property
    def v0(self) -> float: ...
    @property
    def v1(self) -> float: ...
    @property
    def vc(self) -> float: ...
    @property
    def ta(self) -> float: ...
    @property
    def td(self) -> float: ...
    @property
    def pa(self) -> float: ...
    @property
    def pd(self) -> float: ...
    @property
    def ac(self) -> float: ...
    @property
    def de(self) -> float: ...

class version:
    @staticmethod
    def check(major: int = 0, minor: int = 0, patch: int = 0) -> int: ...
    def __init__(self, major: int = 0, minor: int = 0, third: int = 0, extra: int = 0) -> None: ...
    def __lt__(self, that: version) -> bool: ...
    def __gt__(self, that: version) -> bool: ...
    def __le__(self, that: version) -> bool: ...
    def __ge__(self, that: version) -> bool: ...
    def __eq__(self, that: version) -> bool: ...
    def __ne__(self, that: version) -> bool: ...
    def parse(self, ver: bytes | str) -> version: ...
    def cmp(self, that: version) -> int: ...
    @property
    def major(self) -> int: ...
    @major.setter
    def major(self, major: int) -> None: ...
    @property
    def minor(self) -> int: ...
    @minor.setter
    def minor(self, minor: int) -> None: ...
    @property
    def third(self) -> int: ...
    @third.setter
    def third(self, third: int) -> None: ...
    @property
    def extra(self) -> int: ...
    @extra.setter
    def extra(self, extra: int) -> None: ...
    @property
    def alpha(self) -> bytes: ...
    @alpha.setter
    def alpha(self, alpha: bytes | str) -> None: ...
    MAJOR: int
    MINOR: int
    PATCH: int
    TWEAK: int

VERSION: str
