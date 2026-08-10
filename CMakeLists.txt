cmake_minimum_required(VERSION 3.5)
project(i2pwebpage)

set(WITH_BINARY OFF CACHE BOOL "" FORCE)
set(WITH_LIBRARY ON CACHE BOOL "" FORCE)

add_executable(i2pwebpage src/main.cpp)

#libi2pd
add_subdirectory(external/i2pd/build)
target_include_directories(i2pwebpage PRIVATE external/i2pd)
target_link_libraries(i2pwebpage PRIVATE libi2pd)

