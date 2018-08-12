cmake_minimum_required(VERSION 3.0)
project(opengl-stickyman CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(opengl-stickyman
        opengl-stickyman.cpp
        opengl-stickyman.h
        drawFunction.cpp
        drawFunction.h
        globals.cpp
        globals.h
        )
target_link_libraries(opengl-stickyman GL glut GLU)

add_executable(libmath_test libmath_test.cpp)
target_link_libraries(libmath_test gtest pthread)
