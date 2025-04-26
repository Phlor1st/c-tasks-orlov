cmake_minimum_required(VERSION 3.29)
project(labyrinth)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

add_executable(labyrinth
        src/main.cpp
        src/labyrinth.cpp
        src/LabyrinthPathFinder.cpp
        include/LabyrinthPathFinder.h
        src/LabyrinthPathFinder.cpp
)



include_directories(include)

add_executable(test
        tests/tests.cpp
        src/labyrinth.cpp
)

target_link_libraries(test gtest)