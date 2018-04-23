cmake_minimum_required(VERSION 3.6)
project(WorldDomination)
set (gtest_SOURCE_DIR "./googletest")

add_subdirectory(googletest)
include_directories(./googletest/include googletest)

#this is how it is supposed to work
# http://www.kaizou.org/2014/11/gtest-cmake/
#add_library(libgtest IMPORTED STATIC GLOBAL)
#add_dependencies(libgtest gtest)

#set_target_properties(libgtest PROPERTIES "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a" "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -lpthread") # #-std=c++11")

set(SOURCE_FILES Agent.cpp Agent.h Environment.cpp Environment.h Num2DTable.cpp Num2DTable.h qValues.h)

add_executable(WD_Test testMain.cpp ${SOURCE_FILES})
add_executable(WorldDomination main.cpp ${SOURCE_FILES})
target_link_libraries(WD_Test gtest gtest_main)
#target_link_libraries(WD_Test googletest/include/gtest googletest/gtest_main)
#target_link_libraries(WD_Test pthread ${GTEST_BOTH_LIBRARIES} ${Boost_LIBS})

#add_test(WD_Test WD_Test)
set_target_properties(WorldDomination PROPERTIES LINKER_LANGUAGE CXX)