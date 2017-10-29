#!/bin/sh

#Script to load compiler modules and dependent software
export srcdir='../src'
export cpputilssrc='../submodules/cpp-utils/src'

#GNU compiler on raijin.nci.org.au
#module load rjmcmcmt/gnu
#export cxx=g++
#export mpicxx=mpiCC
#export cxxflags='-std=c++11 -O3 -Wall -fdiagnostics-color=always'


#Intel compiler on raijin.nci.org.au
export cxx=icpc
export cxxflags='-std=c++11 -O3 -Wall -diag-disable remark'

export exedir='../bin/raijin'
make -f splitasciibycolumn.make $1
make -f subsetascii.make $1
make -f subsampleascii.make $1
