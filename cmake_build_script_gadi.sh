#!/bin/sh

module load cmake/3.16.2

module load intel-compiler
export BUILD_DIR=$PWD/build-intel
export INSTALL_DIR=$PWD/bin/gadi-intel
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -DCMAKE_C_COMPILER=icc -DCMAKE_CXX_COMPILER=icpc -DCMAKE_BUILD_TYPE=Release  ..

#module load gcc/11.1.0
#export BUILD_DIR=$PWD/build-gnu
#export INSTALL_DIR=$PWD/bin/gadi-gnu
#mkdir $BUILD_DIR
#cd $BUILD_DIR
#cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release  ..

#module list 

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

#cmake --install . --prefix /g/data/qi71/apps/utility-programs/gadi/intel
#cmake --install . --prefix /g/data/qi71/apps/utility-programs/gadi/gnu
