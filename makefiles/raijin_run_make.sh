#!/bin/sh

#Script to load compiler modules and dependent software
export srcdir='../src'
export cpputilssrc='../submodules/cpp-utils/src'

#GNU compiler on raijin.nci.org.au
#module load gcc/5.2.0
#export cxx=g++
#export cxxflags='-std=c++11 -O3 -Wall -fdiagnostics-color=always'
#export exedir='../bin/raijin/gnu'

#Intel compiler on raijin.nci.org.au
module load gcc/5.2.0
module load intel-cc/2018.1.163
export cxx=icpc
export cxxflags='-std=c++11 -O3 -Wall -diag-disable remark'
export exedir='../bin/raijin/intel'

make -f splitasciibycolumn.make $1
make -f subsampleascii.make $1
make -f subsetascii.make $1
make -f subsetasciibypolygon.make $1
make -f changetext.make $1
make -f mvglobal.make $1

