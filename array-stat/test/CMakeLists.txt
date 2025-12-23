include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

include_directories("../")

add_executable(testsa test_statarray.cpp ../ArrayStat.cpp)
target_link_libraries(testsa gtest gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(testsa)
