cmake_minimum_required(VERSION 3.0)
project(opengl-stickyman CXX)

add_executable(opengl-stickyman
        opengl-stickyman.cpp
        opengl-stickyman.h
        drawFunction.cpp
        drawFunction.h
        globals.cpp
        globals.h
        )
target_link_libraries(opengl-stickyman GL glut GLU)

