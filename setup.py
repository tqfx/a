#!/usr/bin/env python
from sys import argv
import os, sys

os.chdir(os.path.dirname(os.path.abspath(argv[0])))
if len(argv) < 2:
    sys.argv += ["--quiet", "build_ext", "--inplace"]
try:
    from setuptools.command.build_ext import build_ext
    from setuptools import setup, Extension
except ImportError:
    from distutils.command.build_ext import build_ext
    from distutils.extension import Extension
    from distutils.core import setup
LIBA_OPENMP = os.environ.get("LIBA_OPENMP")
if LIBA_OPENMP:
    LIBA_OPENMP = int(LIBA_OPENMP)
LIBA_FLOAT = os.environ.get("LIBA_FLOAT")
if LIBA_FLOAT:
    LIBA_FLOAT = int(LIBA_FLOAT)
else:
    LIBA_FLOAT = 8
try:
    USE_CYTHON = True
    from Cython.Build import cythonize
except Exception:
    USE_CYTHON = False
from argparse import ArgumentParser
from sys import byteorder
from re import findall
import ctypes.util
import ctypes


def check_math(text=""):
    if sys.platform == "win32":
        path_libm = ctypes.util.find_library("ucrtbase")
        if not path_libm:
            path_libm = ctypes.util.find_msvcrt()
    else:
        path_libm = ctypes.util.find_library("m")
    try:
        libm = ctypes.CDLL(path_libm)
    except Exception:
        return text
    for func in (
        "expm1",
        "log1p",
        "hypot",
        "atan2",
        "csqrt",
        "cpow",
        "cexp",
        "clog",
        "csin",
        "ccos",
        "ctan",
        "csinh",
        "ccosh",
        "ctanh",
        "casin",
        "cacos",
        "catan",
        "casinh",
        "cacosh",
        "catanh",
    ):
        name = "A_HAVE_" + func.upper()
        if LIBA_FLOAT == 0x10:
            func += "l"
        if LIBA_FLOAT == 0x04:
            func += "f"
        try:
            libm[func]
        except Exception:
            continue
        text += "#define %s 1\n" % (name)
    return text


def configure(config):
    with open("setup.cfg", "r") as f:
        version = findall(r"version = (\S+)", f.read())[0]
    major, minor, patch = findall(r"(\d+).(\d+).(\d+)", version)[0]
    order = {"little": 1234, "big": 4321}.get(byteorder)
    vsize = ctypes.sizeof(ctypes.c_void_p(0))
    text = """/* autogenerated by setup.py */
#define A_VERSION "{}"
#define A_VERSION_MAJOR {}
#define A_VERSION_MINOR {}
#define A_VERSION_PATCH {}
#if !defined A_SIZE_POINTER
#define A_SIZE_POINTER {}
#endif /* A_SIZE_POINTER */
#if !defined A_BYTE_ORDER
#define A_BYTE_ORDER {}
#endif /* A_BYTE_ORDER */
{}""".format(
        version, major, minor, patch, vsize, order, check_math()
    )
    with open(config, "wb") as f:
        f.write(text.encode("UTF-8"))


parser = ArgumentParser(add_help=False)
parser.add_argument("-b", "--build-base", default="build")
parser.add_argument("-O", "--link-objects")
args = parser.parse_known_args(argv[1:])
base = args[0].build_base

sources, objects = [], []
config_h = os.path.join(base, "a.setup.h")
a_have_h = os.path.relpath(config_h, "include/a")
define_macros = [("A_HAVE_H", '"' + a_have_h + '"'), ("A_EXPORTS", None)]
if LIBA_FLOAT != 8:
    define_macros += [("A_SIZE_FLOAT", LIBA_FLOAT)]
if USE_CYTHON and os.path.exists("python/src/a.pyx"):
    sources += ["python/src/a.pyx"]
elif os.path.exists("python/src/a.c"):
    sources += ["python/src/a.c"]
if not os.path.exists(base):
    os.makedirs(base)
configure(config_h)

for dirpath, dirnames, filenames in os.walk("src"):
    if args[0].link_objects:
        break
    for filename in filenames:
        source = os.path.join(dirpath, filename)
        if os.path.splitext(source)[-1] == ".c":
            sources.append(source)

ext_modules = [
    Extension(
        name="liba",
        language="c",
        sources=sources,
        include_dirs=["include"],
        define_macros=define_macros,
    )
]
if USE_CYTHON:
    ext_modules = cythonize(  # type: ignore
        ext_modules,
        quiet=True,
    )


class Build(build_ext):  # type: ignore
    def build_extensions(self):
        if self.compiler.compiler_type == "msvc":
            for e in self.extensions:
                if LIBA_OPENMP:
                    e.extra_compile_args += ["/openmp"]
        if not self.compiler.compiler_type == "msvc":
            for e in self.extensions:
                if LIBA_OPENMP:
                    e.extra_compile_args += ["-fopenmp"]
                    e.extra_link_args += ["-fopenmp"]
        if self.compiler.compiler_type == "mingw32":
            self.compiler.define_macro("__USE_MINGW_ANSI_STDIO", 1)
            for e in self.extensions:
                if e.language == "c++":
                    e.extra_link_args += ["-static-libstdc++"]
                e.extra_link_args += ["-static-libgcc"]
                e.extra_link_args += [
                    "-Wl,-Bstatic,--whole-archive",
                    "-lwinpthread",
                    "-Wl,--no-whole-archive",
                ]
        build_ext.build_extensions(self)


setup(
    ext_modules=ext_modules,  # type: ignore
    cmdclass={"build_ext": Build},
)
