#!/bin/sh

# Build script suitable for the gadi.nci.au cluster

module load gcc/13.2.0
export BUILD_DIR=$PWD/build-gnu
export INSTALL_DIR=$PWD/install-gnu
##export INSTALL_DIR=/g/data/qi71/apps/utility-programs/gnu
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -Wno-dev -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..

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

