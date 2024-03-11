# Utility programs for manipulating ASCII geophysical data files
The programs include 
- splitting files by column contents (e.g. line number or flight number)
- sub-sampling (decimating)
- sub-setting by rectangle
- sub-setting by polygon
- text replacement
- global file renaming
- removing the DATA from ASEGGDF data files
- memory report (Windows only)


## Author
Ross C Brodie

## Language
C++

## Cloning
When initially cloning the repository in git it is convenient to use the "--recursive" option so that all the submodules and their respective submodules are initialised and populated with code.

```bash
> cd <directory where you want the repo to go> 
> git clone --recursive git@github.com:rcb547/utility-programs
```

## Building using cmake on Linux or Windows
1. The cmake program uses the file [*CMakeLists.txt*](CMakeLists.txt) to build the executables
2. The simplest form of cmake
```bash
> cd [directory where the utility-programs repo is]  
> mkdir my-build-dir                            // my-build-dir is a temporary directory for building
> cd my-build-dir                               // change to the build-dir
> cmake ..                                      // configure and generate using ../CMakeLists.txt in the directory above
> cmake --build all                             // build all targets
> cmake --install . --prefix my-install-dir     // install the executables, libraries and headers in my-install-dir 
```
3. To choose a specific compiler

Replace  the line
```bash
> cmake ..
```

with, for example, one of these lines
```bash
> cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
> cmake -DCMAKE_C_COMPILER=icc -DCMAKE_CXX_COMPILER=icpc ..
```

4. For a more sophisticated example

See [*cmake_build_script_ubuntu.sh*](`cmake_build_script_ubuntu.sh`).

## Building on Windows with Visual Studio
- You can build the programs with the free Microsoft Visual Studio Community 2022 compiler.
- Visual Studio solution and project files are supplied.
- Open utility-programs\visualstudio\utilities.sln to compile all programs.
- Alternatively open individual program solution files in their respective sub-directories.
