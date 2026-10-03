#!/usr/bin/env bash
# Builds the WebAssembly module of sysmlv2check: build/wasm/out/sysmlv2check.js (ES module) + sysmlv2check.wasm.
# Needs conan 2 and an emsdk (default /usr/lib/emsdk, or $EMSDK_ENV = path of emsdk_env.sh). Downloads the Conan packages once.
#   check/cmake/build-wasm.sh && node check/tests/wasm-smoke.mjs
set -euo pipefail
cd "$(dirname "$0")/../.."
source "${EMSDK_ENV:-/usr/lib/emsdk/emsdk_env.sh}" >/dev/null 2>&1
conan install . -pr:h=check/cmake/emscripten.profile -pr:b=default -b missing -o '&:shared=False' -o '&:with_online=False' \
      -o '&:with_check=True' -c tools.build:skip_test=True --output-folder=build/wasm
cmake -S . -B build/wasm -G Ninja \
      -DCMAKE_TOOLCHAIN_FILE="$PWD/build/wasm/build/Release/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF "-DCMAKE_CXX_FLAGS=-fwasm-exceptions -O2" "-DCMAKE_C_FLAGS=-fwasm-exceptions -O2" \
      -DCMAKE_EXE_LINKER_FLAGS=-fwasm-exceptions -DSYSMLV2_WERROR=OFF -DBUILD_WITH_REST=OFF -DBUILD_WITH_SERVICES=OFF \
      -DBUILD_WITH_ONLINE=OFF -DBUILD_TESTING=OFF -DBUILD_WITH_PARSING=ON -DBUILD_WITH_CHECK=ON
cmake --build build/wasm --target sysmlv2check-wasm
ls -l build/wasm/out/sysmlv2check.js build/wasm/out/sysmlv2check.wasm
