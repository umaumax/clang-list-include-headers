#!/usr/bin/env bash
set -e
[[ $# == 0 ]] && echo "$0 <target header>" && exit 1
target=$1
INCLUDE_DIRS="$(llvm-config --cxxflags | tr ' ' '\n' | grep -o '\-I.*')"
clang++ -x c++-header -std=c++11 <(cat $target | grep -o '#include ".*"') -o $target.pch $INCLUDE_DIRS
