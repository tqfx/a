#!/usr/bin/env node
var liba = require("../liba")
var ctx = new liba.hpf(10, 0.01)
ctx.gen(10, 0.01).zero()
console.log(ctx.iter(1.0), ctx.iter(1.0))
console.log(ctx.alpha, ctx.output, ctx.input)
ctx.delete()
var ctx = new liba.hpf(0.1)
console.log(ctx.iter(1.0), ctx.iter(1.0))
console.log(ctx.alpha, ctx.output, ctx.input)
ctx.delete()
