include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

include_directories("../")

add_executable(testa test_anagrams.cpp)
target_link_libraries(testa gtest gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(testa)
