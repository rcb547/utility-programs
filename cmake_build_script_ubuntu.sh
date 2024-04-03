#!/bin/sh

# BUILD_DIR is a temporary directory for building (compiling and linking)
export BUILD_DIR=$PWD/build-ubuntu
# INSTALL_DIR is the directory for installing the build package
export INSTALL_DIR=$PWD/install-ubuntu
#export INSTALL_DIR=/usr/share/utility-programs

#Maybe delete the BUILD_DIR for a fresh start
rm -r $BUILD_DIR

mkdir $BUILD_DIR
cd $BUILD_DIR

#Example for the GNU compilers
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release ..

#Build everything (all targets)
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




