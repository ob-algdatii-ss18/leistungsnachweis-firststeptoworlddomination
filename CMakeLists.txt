cmake_minimum_required(VERSION 3.6)
project(WorldDomination)

set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Agent.cpp Agent.h Environment.cpp Environment.h QValues.cpp QValues.h)
add_executable(WorldDomination ${SOURCE_FILES})