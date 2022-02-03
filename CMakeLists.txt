cmake_minimum_required(VERSION 3.20)

project(BaseBuses)


include_directories(include/DataBase)
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