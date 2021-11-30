cmake_minimum_required(VERSION 3.5)

project(testEPoll1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories()
link_directories()

add_executable(testEPoll1 main.cpp ktcpclient1.cpp ktcpserver1.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

target_link_libraries(testEPoll1 pthread)
