cmake_minimum_required(VERSION 3.12)

# Set project name
project(utility-programs)

message(STATUS Build Type = ${CMAKE_BUILD_TYPE})

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Configure find package
#find_package(PkgConfig REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-but-set-variable -Wno-sign-compare -Wno-format-security")
SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -O3 -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-but-set-variable -Wno-sign-compare -Wno-format-security")
if(CMAKE_COMPILER_IS_GNUCC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -Wno-date-time")
	SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wno-unused-result -Wno-date-time")
	#On GCC, even with -Wno-date-time, still get warings of the form: warning: macro "__DATE__" might prevent reproducible builds [-Wdate-time]
endif()

# Adding filesystem library
link_libraries(-lstdc++fs)

# Add the include directories
include_directories(src/)
include_directories(submodules/cpp-utils/src/)
include_directories(submodules/csv-parser/single_include/)

# Add the cpp-utils library submodule
add_subdirectory(submodules/cpp-utils)

# Add the executables
set(tar "splitasciibycolumn")
add_executable(${tar}.exe src/${tar}.cpp)
target_link_libraries(${tar}.exe PRIVATE cpp-utils-static)
install(TARGETS ${tar}.exe DESTINATION .)

set(tar "subsampleascii")
add_executable(${tar}.exe src/${tar}.cpp)
target_link_libraries(${tar}.exe PRIVATE cpp-utils-static)
install(TARGETS ${tar}.exe DESTINATION .)

set(tar "subsetascii")
add_executable(${tar}.exe src/${tar}.cpp)
target_link_libraries(${tar}.exe PRIVATE cpp-utils-static)
install(TARGETS ${tar}.exe DESTINATION .)

set(tar "subsetasciibypolygon")
add_executable(${tar}.exe src/${tar}.cpp)
target_link_libraries(${tar}.exe PRIVATE cpp-utils-static)
install(TARGETS ${tar}.exe DESTINATION .)

set(tar "mvglobal")
add_executable(${tar}.exe src/${tar}.cpp)
target_link_libraries(${tar}.exe PRIVATE cpp-utils-static)
install(TARGETS ${tar}.exe DESTINATION .)

set(tar "changetext")
add_executable(${tar}.exe src/${tar}.cpp)
target_link_libraries(${tar}.exe PRIVATE cpp-utils-static)
install(TARGETS ${tar}.exe DESTINATION .)


