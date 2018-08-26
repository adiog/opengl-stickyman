cmake_minimum_required(VERSION 3.4)
project(OrbitCamera CXX)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O2 -Wall -pedantic")

FILE(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/**.cpp)

ADD_EXECUTABLE(OrbitCamera ${sources})
target_link_libraries(OrbitCamera GL glut GLU)


