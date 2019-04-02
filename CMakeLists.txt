cmake_minimum_required (VERSION 3.5)

project ("DataStructures")

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
  MESSAGE(STATUS "64 bit architecture")
  set(ARCHSUFFIX "x64")
 else()
  MESSAGE(WARNING "32 bit architecture")
  set(ARCHSUFFIX "")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_definitions(-DSOURCEPATH="${CMAKE_SOURCE_DIR}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
  MESSAGE(STATUS "Using Clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  MESSAGE(STATUS "Using GCC")
  # Set c/cpp flag definitions for the compiler.
  set(C_REDUCE_ERRORS "-Wno-unused-parameter -Wno-unused-function -Wno-unknown-pragmas")
  set(CXX_REDUCE_ERRORS "-Wno-unused-parameter -Wno-unused-function -Wno-unknown-pragmas -Wno-reorder -Wno-ignored-qualifiers -Wno-unused-variable -Wno-unused-value")
  set(PEDANTIC "-fPIC -Wall -Wextra -Winline -Wreturn-type -Wuninitialized -Winit-self -fvisibility=hidden")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PEDANTIC} ${CXX_REDUCE_ERRORS} ${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PEDANTIC} ${C_REDUCE_ERRORS} ${CMAKE_C_FLAGS_DEBUG}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
  MESSAGE(STATUS "Using Intel C++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
  MESSAGE(STATUS "Using MSVC")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()

# Set the output folder where your program will be created
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)

# Set other values
set(CMAKE_DEBUG_POSTFIX d)

file(GLOB_RECURSE global_files Code/Global/*.c* Code/Global/*.h* Code/Global/*.inl Code/Global/*.xml Include/*.*)

enable_testing()
add_subdirectory(Code/DataStructures)
add_subdirectory(Code/Sorting)
