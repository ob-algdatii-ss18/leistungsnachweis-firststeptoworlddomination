cmake_minimum_required(VERSION 3.6)
project(WorldDomination)
set (gtest_SOURCE_DIR "googletest")

include_directories(${GTEST_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include/gtest)

#this is how it is supposed to work
# http://www.kaizou.org/2014/11/gtest-cmake/
#add_library(libgtest IMPORTED STATIC GLOBAL)
#add_dependencies(libgtest gtest)

#set_target_properties(libgtest PROPERTIES "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a" "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -lpthread") # #-std=c++11")

set(SOURCE_FILES Agent.cpp Agent.h Environment.cpp Environment.h Num2DTable.cpp Num2DTable.h)

add_executable(WorldDomination main.cpp ${SOURCE_FILES})
add_executable(WD_Test testMain.cpp ${SOURCE_FILES} googletest/include/gtest/gtest.h qValues.h)
target_link_libraries(WD_Test pthread gtest ${GTEST_BOTH_LIBRARIES} ${Boost_LIBS})

set_target_properties(WorldDomination PROPERTIES LINKER_LANGUAGE CXX)