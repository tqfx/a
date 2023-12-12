from a.polytraj5 cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytraj5:
    '''quintic polynomial trajectory'''
    cdef a_polytraj5_s ctx
    def __init__(self, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0 = 0, a_float_t v1 = 0, a_float_t a0 = 0, a_float_t a1 = 0):
        a_polytraj5_gen(&self.ctx, t0, t1, q0, q1, v0, v1, a0, a1)
    def gen(self, a_float_t t0, a_float_t t1, a_float_t q0, a_float_t q1, a_float_t v0 = 0, a_float_t v1 = 0, a_float_t a0 = 0, a_float_t a1 = 0):
        '''generation function'''
        a_polytraj5_gen(&self.ctx, t0, t1, q0, q1, v0, v1, a0, a1)
        return self
    def pos(self, dt):
        '''calculate position'''
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytraj5_pos(&self.ctx, it)
            return out
        return a_polytraj5_pos(&self.ctx, dt)
    def vel(self, dt):
        '''calculate velocity'''
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytraj5_vel(&self.ctx, it)
            return out
        return a_polytraj5_vel(&self.ctx, dt)
    def acc(self, dt):
        '''calculate acceleration'''
        if iterable(dt):
            out = array_num(dt)
            for i, it in enumerate(dt):
                out[i] = a_polytraj5_acc(&self.ctx, it)
            return out
        return a_polytraj5_acc(&self.ctx, dt)
    property q:
        def __get__(self):
            return self.ctx.q
    property v:
        def __get__(self):
            return self.ctx.v
    property a:
        def __get__(self):
            return self.ctx.a