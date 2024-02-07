local subprocess = require("bee.subprocess")
local fs = require("bee.filesystem")
local luamake = fs.exe_path()
assert(subprocess.spawn({ luamake, "lua", "test/a.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/complex.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/mf.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/pid.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/pid_fuzzy.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/pid_neuro.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/tf.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/trajpoly3.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/trajpoly5.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/trajpoly7.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/trajtrap.lua" })):wait()
assert(subprocess.spawn({ luamake, "lua", "test/version.lua" })):wait()
