cmake_minimum_required(VERSION 3.13)

project(tle_download)

set(CMAKE_CXX_STANDARD 20)

add_executable(build main.cpp)

Include(FetchContent)

FetchContent_Declare(
  Requests
  GIT_REPOSITORY https://github.com/elnormous/HTTPRequest.git
  GIT_TAG        v0.3 # or a later release
)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.0 # or a later release
)


FetchContent_MakeAvailable(Requests)
FetchContent_MakeAvailable(Catch2)

add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)