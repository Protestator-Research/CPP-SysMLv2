# Conan host profile for the WebAssembly build of sysmlv2check.
# Needs an activated emsdk (the environment variable EMSDK). compiler.version is the major version of the clang of the emsdk (emsdk 5.0.2: clang 23; Conan 2.31 accepts 22).
[settings]
os=Emscripten
arch=wasm
compiler=clang
compiler.version=22
compiler.libcxx=libc++
compiler.cppstd=20
build_type=Release

[conf]
tools.cmake.cmaketoolchain:user_toolchain=["{{ os.getenv("EMSDK") }}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"]
tools.build:cflags=["-fwasm-exceptions"]
tools.build:cxxflags=["-fwasm-exceptions"]
tools.build:exelinkflags=["-fwasm-exceptions"]
tools.build:sharedlinkflags=["-fwasm-exceptions"]
tools.build:skip_test=True

[options]
antlr4-cppruntime/*:shared=False
boost/*:header_only=True
