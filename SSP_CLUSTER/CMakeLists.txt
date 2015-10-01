cmake_minimum_required(VERSION 3.3)
project(abs_ssp_cluster)

set(SOURCE_FILES abs_ssp_cluster.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "-std=c++14 -D_GLIBCXX_PARALLEL")
set(CMAKE_CXX_COMPILER /usr/local/Cellar/open-mpi/1.10.0/bin/mpic++)

include_directories(/usr/local/Cellar/open-mpi/1.10.0/include)
link_directories(/usr/local/Cellar/open-mpi/1.10.0/lib)

set(CryptoCPP_INCLUDE_DIRS /Users/maxtuno/Dropbox/SDKs/include/cryptopp)
set(CryptoCPP_LIB_DIRS  /Users/maxtuno/Dropbox/SDKs/lib)
set(CryptoCPP_LIBRARIES /Users/maxtuno/Dropbox/SDKs/lib/libcryptopp.a)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.59 COMPONENTS mpi REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${CryptoCPP_INCLUDE_DIRS})
link_directories(${CryptoCPP_LIB_DIRS})
add_executable(abs_ssp_cluster ${SOURCE_FILES})
target_link_libraries(abs_ssp_cluster ${Boost_LIBRARIES} ${CryptoCPP_LIBRARIES} ${CryptoCPP_LIBRARIES} mpi mpi_cxx)