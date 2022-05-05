#!/bin/sh
echo '========================================================================'
echo '========================================================================'
echo '========================================================================'

export compiler=$1
export makemode=$2
export srcdir='../src'
export cpputilssrc='../submodules/cpp-utils/src'

if [ $compiler == 'intel' ] ; then
	echo 'Building with Intel compiler'
	module load intel-compiler
	export cxx=icpc
	export cxxflags='-std=c++11 -O3 -Wall'
	export exedir='../bin/gadi/intel'
elif [ $compiler == 'gnu' ] ; then
	echo 'Building with GCC compiler'
	module load gcc/system
	export cxx=g++
	export cxxflags='-std=c++11 -O3 -Wall -Wno-unknown-pragmas'
	export exedir='../bin/gadi/gnu'
else 
	echo 'Unknow compiler ' $compiler
	exit
fi

export mpicxx=mpiCC
export HAVE_NETCDF=0
export HAVE_GDAL=0
export HAVE_CGAL=0

if [ $HAVE_NETCDF == 1 ] ; then
	echo 'Building with NETCDF'
	export geophysics_netcdf_root='/home/547/rcb547/code/repos/geophysics-netcdf'
	module load netcdf/4.7.1
fi

if [ $HAVE_GDAL == 1 ] ; then
	echo 'Building with GDAL'
	module load gdal/3.0.2
fi

if [ $HAVE_CGAL == 1 ] ; then
	echo 'Building with CGAL'
	module load cgal
fi


module list
echo ---------------------------------------
echo cxx = $cxx
echo mpicxx = $mpicxx ... which is ...
$mpicxx -showme

echo ---------------------------------------

#Compiled 
make -f splitasciibycolumn.make $makemode
make -f subsampleascii.make $makemode
make -f subsetascii.make $makemode
make -f subsetasciibypolygon.make $makemode
make -f changetext.make $makemode
make -f mvglobal.make $makemode