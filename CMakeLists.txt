cmake_minimum_required (VERSION 3.20)
project (ModularSorting LANGUAGES CXX)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(modsort main.cpp)
target_compile_features(modsort PRIVATE cxx_std_23)

target_compile_options(modsort
    PRIVATE
    -Wall -Wextra -Wpedantic
    "$<$<CONFIG:Debug>:-g>"
    "$<$<CONFIG:Release>:-O2>"
)   

enable_testing()
add_subdirectory(test)
