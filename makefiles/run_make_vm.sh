#!/bin/sh

#Script to load compiler modules and dependent software
export exedir='../bin'
export srcdir='../src'
export cpputilssrc='../submodules/cpp-utils/src'

#GNU compiler
export cxx=g++
export cxxflags='-std=c++11 -O3 -Wall -fdiagnostics-color=always'

make -f splitasciibycolumn.make $1
make -f subsetascii.make $1
make -f subsampleascii.make $1


