from typing import Iterable, overload
from array import array

def array_i8(o: object) -> array[int]: ...
def array_u8(o: object) -> array[int]: ...
def array_i16(o: object) -> array[int]: ...
def array_u16(o: object) -> array[int]: ...
def array_i32(o: object) -> array[int]: ...
def array_u32(o: object) -> array[int]: ...
def array_i64(o: object) -> array[int]: ...
def array_u64(o: object) -> array[int]: ...
def array_f32(o: object) -> array[float]: ...
def array_f64(o: object) -> array[float]: ...
def array_num(o: object) -> array[float]: ...
def hash_bkdr(str: bytes, val: int = 0) -> int: ...
def hash_sdbm(str: bytes, val: int = 0) -> int: ...
def isqrt(x: int) -> int: ...
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
    @staticmethod
    @overload
    def __call__(e: int, x: Iterable[float], a: Iterable[float]) -> array[float]: ...
    @staticmethod
    @overload
    def __call__(e: int, x: float, a: Iterable[float]) -> float: ...
    @staticmethod
    @overload
    def gauss(x: Iterable[float], sigma: float, c: float) -> array[float]: ...
    @staticmethod
    @overload
    def gauss(x: float, sigma: float, c: float) -> float: ...
    @staticmethod
    @overload
    def gauss2(
        x: Iterable[float], sigma1: float, c1: float, sigma2: float, c2: float
    ) -> array[float]: ...
    @staticmethod
    @overload
    def gauss2(x: float, sigma1: float, c1: float, sigma2: float, c2: float) -> float: ...
    @staticmethod
    @overload
    def gbell(x: Iterable[float], a: float, b: float, c: float) -> array[float]: ...
    @staticmethod
    @overload
    def gbell(x: float, a: float, b: float, c: float) -> float: ...
    @staticmethod
    @overload
    def sig(x: Iterable[float], a: float, c: float) -> array[float]: ...
    @staticmethod
    @overload
    def sig(x: float, a: float, c: float) -> float: ...
    @staticmethod
    @overload
    def dsig(x: Iterable[float], a1: float, c1: float, a2: float, c2: float) -> array[float]: ...
    @staticmethod
    @overload
    def dsig(x: float, a1: float, c1: float, a2: float, c2: float) -> float: ...
    @staticmethod
    @overload
    def psig(x: Iterable[float], a1: float, c1: float, a2: float, c2: float) -> array[float]: ...
    @staticmethod
    @overload
    def psig(x: float, a1: float, c1: float, a2: float, c2: float) -> float: ...
    @staticmethod
    @overload
    def trap(x: Iterable[float], a: float, b: float, c: float, d: float) -> array[float]: ...
    @staticmethod
    @overload
    def trap(x: float, a: float, b: float, c: float, d: float) -> float: ...
    @staticmethod
    @overload
    def tri(x: Iterable[float], a: float, b: float, c: float) -> array[float]: ...
    @staticmethod
    @overload
    def tri(x: float, a: float, b: float, c: float) -> float: ...
    @staticmethod
    @overload
    def lins(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @staticmethod
    @overload
    def lins(x: float, a: float, b: float) -> float: ...
    @staticmethod
    @overload
    def linz(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @staticmethod
    @overload
    def linz(x: float, a: float, b: float) -> float: ...
    @staticmethod
    @overload
    def s(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @staticmethod
    @overload
    def s(x: float, a: float, b: float) -> float: ...
    @staticmethod
    @overload
    def z(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @staticmethod
    @overload
    def z(x: float, a: float, b: float) -> float: ...
    @staticmethod
    @overload
    def pi(x: Iterable[float], a: float, b: float, c: float, d: float) -> array[float]: ...
    @staticmethod
    @overload
    def pi(x: float, a: float, b: float, c: float, d: float) -> float: ...

class pid:
    RUN: int
    POS: int
    INC: int
    def __init__(self) -> None: ...
    def kpid(self, kp: float, ki: float, kd: float) -> pid: ...
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
    def op(self, op: int) -> pid_fuzzy: ...
    def rule(
        self,
        me: Iterable[Iterable[float]],
        mec: Iterable[Iterable[float]],
        mkp: Iterable[Iterable[float]],
        mki: Iterable[Iterable[float]],
        mkd: Iterable[Iterable[float]],
    ) -> pid_fuzzy: ...
    def set_joint(self, num: int) -> pid_fuzzy: ...
    def kpid(self, kp: float, ki: float, kd: float) -> pid_fuzzy: ...
    def run(self, set: float, fdb: float) -> float: ...
    def pos(self, set: float, fdb: float) -> float: ...
    def inc(self, set: float, fdb: float) -> float: ...
    def zero(self) -> pid_fuzzy: ...
    @property
    def joint(self) -> int: ...
    @joint.setter
    def joint(self, joint: int) -> None: ...
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
    def order(self) -> int: ...

class pid_neuro:
    def __init__(self) -> None: ...
    def kpid(self, k: float, kp: float, ki: float, kd: float) -> pid_neuro: ...
    def wpid(self, wp: float, wi: float, wd: float) -> pid_neuro: ...
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
    def summax(self) -> float: ...
    @summax.setter
    def summax(self, summax: float) -> None: ...
    @property
    def summin(self) -> float: ...
    @summin.setter
    def summin(self, summin: float) -> None: ...
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
def poly_eval(x: Iterable[float], *a: float) -> array[float]: ...
@overload
def poly_eval(x: float, *a: float) -> float: ...
@overload
def poly_evar(x: Iterable[float], *a: float) -> array[float]: ...
@overload
def poly_evar(x: float, *a: float) -> float: ...

class polytraj3:
    def __init__(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
    ) -> None: ...
    def gen(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
    ) -> polytraj3: ...
    @overload
    def pos(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, dt: float) -> float: ...
    @overload
    def vel(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, dt: float) -> float: ...
    @overload
    def acc(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, dt: float) -> float: ...
    @property
    def q(self) -> array[float]: ...
    @property
    def v(self) -> array[float]: ...
    @property
    def a(self) -> array[float]: ...

class polytraj5:
    def __init__(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
    ) -> None: ...
    def gen(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
    ) -> polytraj5: ...
    @overload
    def pos(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, dt: float) -> float: ...
    @overload
    def vel(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, dt: float) -> float: ...
    @overload
    def acc(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, dt: float) -> float: ...
    @property
    def q(self) -> array[float]: ...
    @property
    def v(self) -> array[float]: ...
    @property
    def a(self) -> array[float]: ...

class polytraj7:
    def __init__(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
        j0: float = 0,
        j1: float = 0,
    ) -> None: ...
    def gen(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
        j0: float = 0,
        j1: float = 0,
    ) -> polytraj7: ...
    @overload
    def pos(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, dt: float) -> float: ...
    @overload
    def vel(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, dt: float) -> float: ...
    @overload
    def acc(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, dt: float) -> float: ...
    @overload
    def jer(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def jer(self, dt: float) -> float: ...
    @property
    def q(self) -> array[float]: ...
    @property
    def v(self) -> array[float]: ...
    @property
    def a(self) -> array[float]: ...
    @property
    def j(self) -> array[float]: ...

class tf:
    def __init__(self, num: Iterable[float], den: Iterable[float]) -> None: ...
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
    def __call__(self, x: float) -> float: ...
    def zero(self) -> tf: ...

class version:
    @staticmethod
    def check(major: int = 0, minor: int = 0, patch: int = 0) -> int: ...
    def __init__(self, major: int = 0, minor: int = 0, third: int = 0, extra: int = 0) -> None: ...
    def compare(self, other: version) -> int: ...
    def __lt__(self, other: version) -> bool: ...
    def __gt__(self, other: version) -> bool: ...
    def __le__(self, other: version) -> bool: ...
    def __ge__(self, other: version) -> bool: ...
    def __eq__(self, other: version) -> bool: ...
    def __ne__(self, other: version) -> bool: ...
    def parse(self, ver: bytes) -> version: ...
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
    MAJOR: int
    MINOR: int
    PATCH: int
    TWEAK: int

VERSION: str
