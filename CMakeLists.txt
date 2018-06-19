cmake_minimum_required(VERSION 3.6)
project(WorldDomination)
set (gtest_SOURCE_DIR "./googletest")

add_subdirectory(googletest)

include_directories(./googletest/include googletest)
link_directories(./googletest/lib)

set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x") #-larmadillo -lpthread") # #-std=c++11")

set(SOURCE_FILES Agent.cpp Agent.h Environment.cpp Environment.h Num2DTable.cpp Num2DTable.h qValues.h Policy.h) # Policy.h)

add_executable(WorldDomination main.cpp ${SOURCE_FILES})
#target_link_libraries(WorldDomination arma armadillo) #passt das so?

add_executable(WD_Test testMain.cpp ${SOURCE_FILES})
target_link_libraries(WD_Test gtest gtest_main)


set_target_properties(WorldDomination PROPERTIES LINKER_LANGUAGE CXX)