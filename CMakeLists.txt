cmake_minimum_required(VERSION 2.6)

project(PhotonFactory)

file(GLOB SOURCES src/*.cc)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

add_executable(ray ${SOURCES})
target_link_libraries(ray ${PNG_LIBRARIES} ${LIBXML2_LIBRARIES})

