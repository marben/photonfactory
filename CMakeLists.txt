cmake_minimum_required(VERSION 2.6)

# this has to be bfore the project() command
#set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang++")

project(PhotonFactory)

option(test "Build all tests." ON)

set(COMPILER_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(CMAKE_VERBOSE_MAKEFILE ON)

# using GLOB. listing source files is too annoying at the moment
# ! need to rerun cmake after adding a file
file(GLOB SOURCES src/*.cc)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

# libeigen is found using pkg-config plugin
INCLUDE(FindPkgConfig)
pkg_check_modules(EIGEN3 REQUIRED eigen3)
include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(ray ${SOURCES})

target_link_libraries(ray ${PNG_LIBRARIES} ${LIBXML2_LIBRARIES})

if (test)
	add_subdirectory("external/gtest-1.7.0")

	enable_testing()

	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

	add_executable(runUnitTests "test/runUnitTests.cc")
	target_link_libraries(runUnitTests gtest gtest_main pthread)

	add_test(
		NAME runUnitTests
		COMMAND runUnitTests
		)
endif()
