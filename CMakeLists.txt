cmake_minimum_required(VERSION 3.5)
project(hauer_on_repeat)
set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTS "test/*.cpp" "src/*.cpp")

list(FILTER TESTS EXCLUDE REGEX ".*main.cpp")

find_package(Threads)
include_directories(include)


add_executable(hauer_on_repeat ${SOURCES} src/main.cpp)
target_link_libraries(hauer_on_repeat ${CMAKE_THREAD_LIBS_INIT})
add_executable(runTests ${TESTS})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)