cmake_minimum_required (VERSION 3.20)
project (Anagrams LANGUAGES CXX)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(ana main.cpp)
target_compile_features(ana PRIVATE cxx_std_23)

target_compile_options(ana
    PRIVATE
    -Wall -Wextra -Wpedantic
    "$<$<CONFIG:Debug>:-g>"
    "$<$<CONFIG:Release>:-O2>"
)   

enable_testing()
add_subdirectory(test)
