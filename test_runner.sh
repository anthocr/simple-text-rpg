#!/usr/bin/env sh

set -eu

# /usr/src is a bind mount when this runs in cpp-container.  Do not place the
# CMake cache there: a cache created on the host records host paths and cannot
# be reused from the container.
build_dir="${BUILD_DIR:-/tmp/text-rpg-build}"

cmake -S . -B "$build_dir"
cmake --build "$build_dir"
exec "$build_dir/text_rpg"
