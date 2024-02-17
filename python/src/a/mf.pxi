from a.mf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
@cython.auto_pickle(False)
cdef class mf:
    NUL    = A_MF_NUL
    GAUSS  = A_MF_GAUSS
    GAUSS2 = A_MF_GAUSS2
    GBELL  = A_MF_GBELL
    SIG    = A_MF_SIG
    DSIG   = A_MF_DSIG
    PSIG   = A_MF_PSIG
    TRAP   = A_MF_TRAP
    TRI    = A_MF_TRI
    LINS   = A_MF_LINS
    LINZ   = A_MF_LINZ
    S      = A_MF_S
    Z      = A_MF_Z
    PI     = A_MF_PI
    @staticmethod
    def __call__(e: int, x, a):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        cdef array a_ = array_num(a)
        cdef a_float *a_p = <a_float *>a_.data.as_voidptr
        cdef int m = e
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf(m, p[i], a_p)
            return y
        return a_mf(m, x, a_p)
    @staticmethod
    def gauss(x, sigma: a_float, c: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_gauss(p[i], sigma, c)
            return y
        return a_mf_gauss(x, sigma, c)
    @staticmethod
    def gauss2(x, sigma1: a_float, c1: a_float, sigma2: a_float, c2: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_gauss2(p[i], sigma1, c1, sigma2, c2)
            return y
        return a_mf_gauss2(x, sigma1, c1, sigma2, c2)
    @staticmethod
    def gbell(x, a: a_float, b: a_float, c: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_gbell(p[i], a, b, c)
            return y
        return a_mf_gbell(x, a, b, c)
    @staticmethod
    def sig(x, a: a_float, c: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_sig(p[i], a, c)
            return y
        return a_mf_sig(x, a, c)
    @staticmethod
    def dsig(x, a1: a_float, c1: a_float, a2: a_float, c2: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_dsig(p[i], a1, c1, a2, c2)
            return y
        return a_mf_dsig(x, a1, c1, a2, c2)
    @staticmethod
    def psig(x, a1: a_float, c1: a_float, a2: a_float, c2: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_psig(p[i], a1, c1, a2, c2)
            return y
        return a_mf_psig(x, a1, c1, a2, c2)
    @staticmethod
    def trap(x, a: a_float, b: a_float, c: a_float, d: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_trap(p[i], a, b, c, d)
            return y
        return a_mf_trap(x, a, b, c, d)
    @staticmethod
    def tri(x, a: a_float, b: a_float, c: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_tri(p[i], a, b, c)
            return y
        return a_mf_tri(x, a, b, c)
    @staticmethod
    def lins(x, a: a_float, b: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_lins(p[i], a, b)
            return y
        return a_mf_lins(x, a, b)
    @staticmethod
    def linz(x, a: a_float, b: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_linz(p[i], a, b)
            return y
        return a_mf_linz(x, a, b)
    @staticmethod
    def s(x, a: a_float, b: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_s(p[i], a, b)
            return y
        return a_mf_s(x, a, b)
    @staticmethod
    def z(x, a: a_float, b: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_z(p[i], a, b)
            return y
        return a_mf_z(x, a, b)
    @staticmethod
    def pi(x, a: a_float, b: a_float, c: a_float, d: a_float):
        cdef array y
        cdef a_float *p
        cdef Py_ssize_t i
        cdef Py_ssize_t n
        if PyObject_HasAttrString(x, "__contains__"):
            n = len(x)
            y = array_num(x)
            p = <a_float *>y.data.as_voidptr
            for i in prange(n, nogil=True):
                p[i] = a_mf_pi(p[i], a, b, c, d)
            return y
        return a_mf_pi(x, a, b, c, d)
