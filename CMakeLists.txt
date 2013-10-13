cmake_minimum_required(VERSION 2.6)

project(PhotonFactory)

#set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang")

set(COMPILER_FLAGS "-Wall")
set(CMAKE_C_FLAGS ${COMPILER_FLAGS})
set(CMAKE_CXX_FLAGS ${COMPILER_FLAGS})

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

file(GLOB SOURCES src/*.cc)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})


#set(EIGEN_INCLUDE_DIR /usr/include/eigen2)
#include_directories(${EIGEN_INCLUDE_DIR})

include_directories("extern/eigen")

add_executable(ray ${SOURCES})
target_link_libraries(ray ${PNG_LIBRARIES} ${LIBXML2_LIBRARIES})

