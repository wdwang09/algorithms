cmake_minimum_required(VERSION 3.0)
project(Algorithms LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

include_directories(common)

add_subdirectory(binary_search)
add_subdirectory(binary_tree)
add_subdirectory(data_structure)
add_subdirectory(disjoint_set)
add_subdirectory(graph)
add_subdirectory(priority_queue)
add_subdirectory(sort)
