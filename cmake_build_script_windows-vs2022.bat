@ECHO off

REM Run this script from the "X64 Native Tools Command Prompt for VS 2019 (or VS 2022)" so that all the compiler stuff is set up

REM BUILD_DIR is a temporary directory for building (compiling and linking)
set BUILD_DIR=%cd%\build-windows-vs2022

REM Optionally delete the BUILD_DIR to ensure a clean cache/start
REM DEL /S/Q %BUILD_DIR%

REM INSTALL_DIR is the directory for installing the built package and examples (e.g. c:\myprograms\ga-aem)
set INSTALL_DIR=%cd%\install-windows-vs2022
REM set INSTALL_DIR=%LocalAppData%\utility-programs
REM set INSTALL_DIR=C:\Users\<your_username>\AppData\Local\utility-programs

REM Maybe delete the BUILD_DIR for a fresh start
REM RMDIR /S /Q %BUILD_DIR%

REM Create and cd to the BUILD_DIR
mkdir %BUILD_DIR%
cd    %BUILD_DIR%

REM First generate the build cache first
REM cmake -Wno-dev -G "Visual Studio 16 2019" -A x64 -DCMAKE_CXX_COMPILER=msvc ..
cmake -Wno-dev -G "Visual Studio 17 2022" -A x64 -DCMAKE_CXX_COMPILER=msvc ..

REM Build everything
cmake --build . --config=Release

REM Or alternatively ...

REM Build only particular targets
REM cmake --build . --target splitasciibycolumn --config=Release
REM cmake --build . --target subsampleascii --config=Release
REM cmake --build . --target subsetascii --config=Release
REM cmake --build . --target subsetasciibypolygon --config=Release
REM cmake --build . --target removedata --config=Release
REM cmake --build . --target mvglobal --config=Release
REM cmake --build . --target changetext --config=Release
REM cmake --build . --target memory --config=Release

cmake --install . --prefix %INSTALL_DIR%

cd ..
PAUSE









