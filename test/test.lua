local platform = require("bee.platform")
local subprocess = require("bee.subprocess")
local ext = platform.os == "windows" and ".exe" or ""
assert(subprocess.spawn({ "build/bin/a" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/avl" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/buf" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/complex" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/crc" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/hpf" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/list" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/lpf" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/main" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/math" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/mf" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/notefreqs" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/operator" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/pid" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/pid_expert" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/pid_fuzzy" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/pid_neuro" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/poly" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/polytraj3" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/polytraj5" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/polytraj7" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/que" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/rbf" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/rbt" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/tf" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/str" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/slist" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/utf" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/vec" .. ext })):wait()
assert(subprocess.spawn({ "build/bin/version" .. ext })):wait()
