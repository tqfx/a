import * as a from "liba.so";
var ctx = new a.polytrack5(0, 1, 0, 1)
ctx.gen(0, 10, 0, 10, 0, 0)
for (var i = 0; i < 10; i += 0.1) {
    console.log(i, ctx.pos(i), ctx.vel(i), ctx.acc(i))
}
