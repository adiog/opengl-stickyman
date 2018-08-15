cmake_minimum_required(VERSION 3.0)
project(opengl-stickyman CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(source)

#add_executable(opengl-stickyman
#        opengl-stickyman.cpp
#        opengl-stickyman.h
#        drawFunction.cpp
#        drawFunction.h
#        globals.cpp
#        globals.h
#        )
#target_link_libraries(opengl-stickyman GL glut GLU)

file(GLOB_RECURSE sources source/**.cpp)
file(GLOB_RECURSE headers source/**.h)
add_executable(vrsuit ${sources} ${headers})
target_link_libraries(vrsuit GL glut GLU)


add_executable(libbla_test test/libbla_test.cpp source/math/LinearAlgebra.cpp source/math/LinearAlgebra.h source/math/MathTypes.cpp)
target_link_libraries(libbla_test gtest pthread)
