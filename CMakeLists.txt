cmake_minimum_required(VERSION 3.6)
project(WorldDomination)
set (gtest_SOURCE_DIR "googletest")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include/gtest)


set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x") #-std=c++11")

set(SOURCE_FILES Agent.cpp Agent.h Environment.cpp Environment.h Num2DTable.cpp Num2DTable.h)

add_executable(WorldDomination main.cpp ${SOURCE_FILES})
add_executable(WD_Test testMain.cpp ${SOURCE_FILES} ${gtest_SOURCE_DIR}/include/gtest/gtest.h)

set_target_properties(WorldDomination PROPERTIES LINKER_LANGUAGE CXX)