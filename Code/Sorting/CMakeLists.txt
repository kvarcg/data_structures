set(PROJECT_NAME "Sorting")
message(STATUS "Building Sorting" )

set(INCLUDE_DIR
   "${CMAKE_SOURCE_DIR}/Code/Global"
   "${CMAKE_SOURCE_DIR}/Code/DataStructures"
   "${CMAKE_SOURCE_DIR}/Code/Sorting")

file(GLOB_RECURSE include_files *.h* *.inl *.xml)
include_directories(${INCLUDE_DIR})

add_executable(test_sorting Tests/SortingTests.cpp Sorting.h Sorting.inl ${global_files})

add_test(sorting test_sorting)
