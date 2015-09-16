cmake_minimum_required(VERSION 3.3)
project(abs_primality CXX)

set(SOURCE_FILES abs_primality.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "-std=c++11")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(abs_primality ${SOURCE_FILES})
target_link_libraries(abs_primality ${Boost_LIBRARIES})
