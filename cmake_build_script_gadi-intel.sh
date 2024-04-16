#!/bin/sh

# Build script suitable for the gadi.nci.au cluster

module load intel-compiler-llvm/2024.0.2
export BUILD_DIR=$PWD/build-intel
export INSTALL_DIR=$PWD/install-intel
###export INSTALL_DIR=/g/data/qi71/apps/utility-programs/intel
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -DCMAKE_C_COMPILER=icx -DCMAKE_CXX_COMPILER=icpx ..

module list 

#Build everything
cmake --build . --target all

#Or alternatively ...

#Build only particular targets
#cmake --build . --target splitasciibycolumn
#cmake --build . --target subsampleascii
#cmake --build . --target subsetascii
#cmake --build . --target subsetasciibypolygon
#cmake --build . --target removedata
#cmake --build . --target mvglobal
#cmake --build . --target changetext

cmake --install . --prefix $INSTALL_DIR

