import * as a from "liba.so";
var ctx = new a.lpf(10, 0.01)
ctx.gen(10, 0.01)
ctx.iter(1)
console.log(ctx.alpha)
console.log(ctx.output)
var ctx = new a.lpf(0.1)
ctx.gen(0.1)
ctx.iter(1)
console.log(ctx.alpha)
console.log(ctx.output)
ctx.zero()
