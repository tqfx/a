#!/usr/bin/env lua

---@diagnostic disable: redefined-local
package.path = arg[0]:sub(0, -arg[0]:match("([^/\\]*)$"):len() - 1) .. "?.lua;" .. package.path
local test = require("test")
local a = require("liba")
test.dir(getmetatable(a.tf))

local num = { 6.59492796e-05, 6.54019884e-05 }
local den = { -1.97530991, 0.97530991 }

local ctx = a.tf.new(num, den)
test.dir(getmetatable(ctx))
assert(type(a.tf.iter(ctx, 1)) == "number")
assert(type(a.tf.zero(ctx)) == "userdata")
---@diagnostic disable: param-type-mismatch, redundant-parameter
assert(type(a.tf:iter(ctx, 1)) == "number")
assert(type(a.tf:zero(ctx)) == "userdata")
---@diagnostic enable: param-type-mismatch, redundant-parameter
local ctx = a:tf(num, den)
assert(type(ctx.iter(ctx, 1)) == "number")
assert(type(ctx.zero(ctx)) == "userdata")
assert(type(ctx:iter(1)) == "number")
assert(type(ctx:zero()) == "userdata")
test.dir(ctx.num)
test.dir(ctx.den)
test.dir(ctx.input)
test.dir(ctx.output)
ctx.num = { 1, 2 }
assert(type(ctx.num) == "table")
ctx.den = { 3, 4 }
assert(type(ctx.den) == "table")
