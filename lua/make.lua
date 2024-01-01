local lm = require("luamake")
lm:lua_library("liba")({
    defines = { "A_EXPORTS" },
    includes = { "../include" },
    sources = { "../src/*.c*", "src/*.c*" },
    links = lm.os ~= "windows" and { "m" } or {},
})
