# Utilities for manipulating ASCII geophysical data files
## Description
The repository contains simple utility programs for:
- Splitting files by column contents (eg. line number or flight number)
- Sub-sampling (decimating)
- Sub-setting by spatial rectangle
- Sub-setting by spatial polygon
- Removing the DATA column from ASEGGDF data files
- Text replacement
- Global file renaming
- Memory usage report (Windows only)
## Author
Ross C Brodie
## Language
C++
## Cloning
When initially cloning the repository in git it is convenient to use the "--recursive" option so that all the submodules and their respective submodules are initialised and populated with code.
```bash
    >> cd <directory where you want the repo to be cloned into, eg., ~/myrepos> 
    >> git clone --recursive git@github.com:rcb547/utility-programs
```
## Building using cmake on Linux or Windows
1. The cmake program uses the file [*CMakeLists.txt*](CMakeLists.txt) to build the executables
1. The simplest form of cmake usage is,
    ```bash
    >> cd <directory where the utility-programs repo is> // eg. cd ~/myrepos/utility-programs>  
    >> mkdir <my-build-dir>                              // my-build-dir is a temporary directory for building
    >> cd <my-build-dir>                                 // change to the build-dir
    >> cmake ..                                          // configure and generate using ../CMakeLists.txt in the directory above
    >> cmake --build .                                   // build all targets
    >> cmake --install . --prefix <my-install-dir>       // install the executables, libraries and headers in my-install-dir 
    ```
1. To choose a specific compiler
    Replace  the line
    ```bash
    >> cmake ..
    ```
    with, for example, one of these lines
    ```bash
    >> cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
    >> cmake -DCMAKE_C_COMPILER=icc -DCMAKE_CXX_COMPILER=icpc ..
    ```
1. For more sophisticated cases, see for example, [*cmake_build_script_ubuntu.sh*](cmake_build_script_ubuntu.sh), or [*cmake_build_script_windows-vs2022.bat*](cmake_build_script_windows-vs2022.bat).
1. The executable programs will be installed into a directory named <my-install-dir>/bin, which will need to be in the system search path (PATH environment variable) before it can be executed.
## Building on Windows with Microsoft Visual Studio
- You can build the programs with the free Microsoft Visual Studio Community 2022 compiler.
- Visual Studio solution and project files are supplied.
- Open utility-programs\visualstudio\utilities.sln to compile all programs.
- Alternatively open individual program solution files in their respective sub-directories.
## Program usage
The programs include utilities for:
- Splitting files by column contents (eg. line number or flight number)
```bash
    >> splitasciibycolumn.exe
    usage: splitasciibycolumn.exe input_file column_number [headerlines]
```

- Sub-sampling (decimating)
```bash
    >> subsampleascii.exe
    usage: subsampleascii.exe input_file output_file subsample_rate
```

- Sub-setting by spatial rectangle
```bash
    >> subsetascii.exe
    usage: subsetascii.exe input_file output_file x_column y_column x_low x_high y_low y_high [subsample] [headerlines]
```

- Sub-setting by spatial polygon
```bash
    >> subsetasciibypolygon.exe
    usage: subsetasciibypolygon.exe input_file output_file polygon_file x_column y_column subsample_rate
```

- Removing the DATA column from ASEGGDF data files
```bash
    >> removedata.exe
    usage: removedata.exe input_file output_file
```

- Text replacement
```bash
    >> changetext.exe
    usage: changetext.exe input_file search_pattern replace_pattern
           You need to enclose strings with embedded spaces with " " marks
           /t represents tab
           /r carriage return
           /n new line
```

- Global file renaming
```bash
    >> mvglobal.exe
    usage: mvglobal.exe [-i] [-start] [-end] file_search_pattern file_replace_pattern
    This program renames files/directories/links, in the CURRENT DIRECTORY, the names of which contain the SEARCH PATTERN, to the corrosponding name containing the REPLACE PATTERN.
    The USER MUST have WRITE permission
    -i          - prompts for confirmation
    -start      - only at the start of the filename
    -end        - only at the end of the filename
    -start -end - either at the start or end of the filename
    Do NOT use the * character as a wildcard
```

- Memory usage report (Windows only)
```bash
    >> memory.exe
    usage: mvglobal.exe
```