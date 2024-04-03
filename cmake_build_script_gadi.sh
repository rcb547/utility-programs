#!/bin/sh

# Build script suitable for the gadi.nci.au cluster

module load cmake/3.16.2

module load intel-compiler/2021.10.0
export BUILD_DIR=$PWD/build-intel
export INSTALL_DIR=$PWD/install-intel
###export INSTALL_DIR=/g/data/qi71/apps/utility-programs/intel
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -DCMAKE_CXX_COMPILER=icpc -DCMAKE_BUILD_TYPE=Release  ..

#module load gcc/13.2.0
#export BUILD_DIR=$PWD/build-gnu
#export INSTALL_DIR=$PWD/install-gnu
###export INSTALL_DIR=/g/data/qi71/apps/utility-programs/gnu
#mkdir $BUILD_DIR
#cd $BUILD_DIR
#cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release  ..

module list 


#Build everything
cmake --build . --target all

#Or alternatively ...

#Build only particular targets
#cmake --build . --target splitasciibycolumn --config=Release
#cmake --build . --target subsampleascii --config=Release
#cmake --build . --target subsetascii --config=Release
#cmake --build . --target subsetasciibypolygon --config=Release
#cmake --build . --target removedata --config=Release
#cmake --build . --target mvglobal --config=Release
#cmake --build . --target changetext --config=Release

cmake --install . --prefix $INSTALL_DIR

