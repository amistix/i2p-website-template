cmake_minimum_required(VERSION 3.5)
project(i2pwebpage)

set(CMAKE_POLICY_DEFAULT_CMP0167 OLD)

set(WITH_BINARY OFF CACHE BOOL "" FORCE)
set(WITH_LIBRARY ON CACHE BOOL "" FORCE)

add_executable(i2pwebsite src/main.cpp)

#libi2pd
add_subdirectory(external/i2pd/build)
target_include_directories(i2pwebsite PRIVATE external/i2pd)
target_link_libraries(i2pwebsite PRIVATE libi2pd)

