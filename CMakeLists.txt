cmake_minimum_required(VERSION 3.29)
project(image)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

add_executable(image
        src/main.cpp
        src/image.cpp
        include/image.h
)

include_directories(include)

add_executable(tests
        include/image.h
        src/image.cpp
        tests/tests.cpp
)

target_link_libraries(tests gtest)