cmake_minimum_required(VERSION 3.3)
project(abs_cracker)

set(SOURCE_FILES abs_cracker.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "-std=c++11")

set(CryptoCPP_INCLUDE_DIRS /Users/maxtuno/Dropbox/SDKs/include/cryptopp)
set(CryptoCPP_LIB_DIRS  /Users/maxtuno/Dropbox/SDKs/lib)
set(CryptoCPP_LIBRARIES /Users/maxtuno/Dropbox/SDKs/lib/libcryptopp.a)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS} ${CryptoCPP_INCLUDE_DIRS})
link_directories(${CryptoCPP_LIB_DIRS})
add_executable(abs_cracker ${SOURCE_FILES})
target_link_libraries(abs_cracker ${Boost_LIBRARIES} ${CryptoCPP_LIBRARIES})