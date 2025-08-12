#!/bin/sh

# Note: Changing this script WILL NOT affect how CodeCrafters runs your program.
# Learn more: https://codecrafters.io/program-interface

set -e

(
  cd "$(dirname "$0")"
  cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
  cmake --build ./build
)

exec $(dirname $0)/build/interpreter "$@"
