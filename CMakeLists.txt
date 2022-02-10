cmake_minimum_required(VERSION 3.20)

project(BaseBuses)

#SET(MYCOMPILE_FLAGS "-Wall -Wextra")

set(Test 1)

if(Test EQUAL 1)
    message("I`m good")
    set(CMAKE_C_COMPILER "clang++-9")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++-9")

    set(MYCOMPILE_FLAGS "-std=c++17 -pedantic  -fsanitize=address -g -fno-omit-frame-pointer -fno-optimize-sibling-calls")
    set(CMAKE_CXX_FLAGS ${MYCOMPILE_FLAGS})

    add_definitions("-D GLIBCXX_DEBUG -D GLIBCXX_DEBUG_PEDANTIC")
endif()


include_directories(include/DataBase)
include_directories(include/DataBase/Router)
include_directories(include/DataBase/Graph)
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