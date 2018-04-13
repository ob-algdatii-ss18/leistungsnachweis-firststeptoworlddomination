cmake_minimum_required(VERSION 3.6)
project(WorldDomination)
set (gtest_SOURCE_DIR "googletest")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include/gtest)


set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x") #-std=c++11")

set(SOURCE_FILES main.cpp Agent.cpp Agent.h Environment.cpp Environment.h Num2DTable.cpp Num2DTable.h ${gtest_SOURCE_DIR}/include/gtest/gtest.h)
add_executable(WorldDomination ${SOURCE_FILES})
set_target_properties(WorldDomination PROPERTIES LINKER_LANGUAGE CXX)