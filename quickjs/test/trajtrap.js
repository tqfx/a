import * as a from "liba.so";
function assert(expr) {
    if (!eval(expr)) {
        throw Error(expr);
    }
}
var ctx = new a.trajtrap();
assert("ctx.gen(2, 2, -2, 0, 4) != undefined");
assert("ctx.t != undefined");
assert("ctx.p0 != undefined");
assert("ctx.p1 != undefined");
assert("ctx.v0 != undefined");
assert("ctx.v1 != undefined");
assert("ctx.vc != undefined");
assert("ctx.ta != undefined");
assert("ctx.td != undefined");
assert("ctx.pa != undefined");
assert("ctx.pd != undefined");
assert("ctx.ac != undefined");
assert("ctx.de != undefined");
for (var i = 0; i < ctx.t; i += ctx.t / 10) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i));
}
