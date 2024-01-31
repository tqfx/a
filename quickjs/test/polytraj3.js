import * as a from "liba.so";
var ctx = new a.polytraj3(1, 0, 1)
ctx.gen(10, 0, 10, 0, 0)
console.log(ctx.q)
console.log(ctx.v)
console.log(ctx.a)
for (var i = 0; i < 10; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i))
}
