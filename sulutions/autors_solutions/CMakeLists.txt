cmake_minimum_required(VERSION 3.20)

project(BaseBuses2)


include_directories(include)


file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)