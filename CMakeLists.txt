cmake_minimum_required(VERSION 3.20)

project(BaseBuses)

#SET(MYCOMPILE_FLAGS "-Wall -Wextra")

set(Sanitizers 1)

if(Sanitizers EQUAL 1)
    message("Compile with Sanitizers")
    set(CMAKE_C_COMPILER "clang++-9")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++-9")

    set(MYCOMPILE_FLAGS "-std=c++17 -pedantic  -fsanitize=address -g -fno-omit-frame-pointer -fno-optimize-sibling-calls")
    set(CMAKE_CXX_FLAGS ${MYCOMPILE_FLAGS})

    add_definitions("-D GLIBCXX_DEBUG -D GLIBCXX_DEBUG_PEDANTIC")
endif()


include_directories(include/DataBase)
include_directories(include/DataBase/Router)
include_directories(include/DataBase/Graph)
include_directories(include/DataBase/BusesMap)
include_directories(include/SVG)
include_directories(include/MachineForCreateBase)
include_directories(include/ParseRequests)
include_directories(include/ProcessingBase)
include_directories(include/Tests)
include_directories(include/Tests/Resources)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
