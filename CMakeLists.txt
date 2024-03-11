#cmake_minimum_required(VERSION 3.12)
cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0076 NEW)
SET(CMAKE_COLOR_MAKEFILE ON)

function(reportvar var)
  message(STATUS "${ARGVN}${var}=${${var}}")
endfunction()

function(reportallvars)
	get_cmake_property(_variableNames VARIABLES)
	list (SORT _variableNames)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
endfunction()

# Set project name
project(utility-programs)

message(STATUS Build Type = ${CMAKE_BUILD_TYPE})

reportvar(CMAKE_SYSTEM_NAME)
reportvar(CMAKE_BUILD_TYPE)

set(CMAKE_EXECUTABLE_SUFFIX_C ".exe")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".exe")

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Set the compile flags
if("${CMAKE_C_COMPILER_ID}" MATCHES "MSVC" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
	SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   /O2")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wno-unused-but-set-variable -Wno-sign-compare -Wno-format-security -Wno-tautological-constant-compare ")
	SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -O3 -Wno-unused-but-set-variable -Wno-sign-compare -Wno-format-security -Wno-tautological-constant-compare ")
	# Adding filesystem library
	link_libraries(-lstdc++fs)
endif()

if(CMAKE_COMPILER_IS_GNUCC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -Wno-date-time -Wno-error=date-time ")
	SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wno-unused-result -Wno-date-time -Wno-error=date-time ")
	#On GCC, even with -Wno-date-time, still get warings of the form: warning: macro "__DATE__" might prevent reproducible builds [-Wdate-time]	
endif()

# Find PkgConfig
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
	message(STATUS "PkgConfig package was found")
else()
	message(STATUS "PkgConfig package was NOT found")
endif()


# Add the include directories
include_directories(src/)
include_directories(submodules/cpp-utils/src/)
include_directories(submodules/csv-parser/single_include/)

# Add the executables
set(tar splitasciibycolumn)
add_executable(${tar} src/${tar}.cpp)
target_sources(${tar} PRIVATE submodules/cpp-utils/src/file_utils.cpp submodules/cpp-utils/src/general_utils.cpp)
install(TARGETS ${tar} DESTINATION bin OPTIONAL)

set(tar subsampleascii)
add_executable(${tar} src/${tar}.cpp)
target_sources(${tar} PRIVATE submodules/cpp-utils/src/file_utils.cpp submodules/cpp-utils/src/general_utils.cpp)
install(TARGETS ${tar} DESTINATION bin OPTIONAL)

set(tar subsetascii)
add_executable(${tar} src/${tar}.cpp)
target_sources(${tar} PRIVATE submodules/cpp-utils/src/file_utils.cpp submodules/cpp-utils/src/general_utils.cpp)
install(TARGETS ${tar} DESTINATION bin OPTIONAL)

set(tar subsetasciibypolygon)
add_executable(${tar} src/${tar}.cpp)
target_sources(${tar} PRIVATE submodules/cpp-utils/src/file_utils.cpp submodules/cpp-utils/src/general_utils.cpp)
install(TARGETS ${tar} DESTINATION bin OPTIONAL)

set(tar removedata)
add_executable(${tar} src/${tar}.cpp)
target_sources(${tar} PRIVATE submodules/cpp-utils/src/file_utils.cpp submodules/cpp-utils/src/general_utils.cpp)
install(TARGETS ${tar} DESTINATION bin OPTIONAL)

set(tar mvglobal)
add_executable(${tar} src/${tar}.cpp)
target_sources(${tar} PRIVATE submodules/cpp-utils/src/file_utils.cpp submodules/cpp-utils/src/general_utils.cpp)
install(TARGETS ${tar} DESTINATION bin OPTIONAL)

set(tar changetext)
add_executable(${tar} src/${tar}.cpp)
target_sources(${tar} PRIVATE submodules/cpp-utils/src/file_utils.cpp submodules/cpp-utils/src/general_utils.cpp)
install(TARGETS ${tar} DESTINATION bin OPTIONAL)

if (MSVC)
	# Only on Windows with MSVC
	set(tar memory)
	add_executable(${tar} src/${tar}.cpp)
	target_sources(${tar} PRIVATE submodules/cpp-utils/src/file_utils.cpp submodules/cpp-utils/src/general_utils.cpp)
	install(TARGETS ${tar} DESTINATION bin OPTIONAL)
endif()
