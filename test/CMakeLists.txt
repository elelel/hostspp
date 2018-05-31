cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(hosts_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(TOP_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PATH)

set(CONTRIB
  ${TOP_DIR}/contrib)

set(SOURCES
  ${SRC}/hosts.cpp)

set(INCLUDE_DIRS
  ${TOP_DIR}/include
  ${CONTRIB}/Catch2/single_include)

add_executable(hosts_test ${SOURCES})
target_include_directories(hosts_test PUBLIC ${INCLUDE_DIRS})
target_compile_definitions(hosts_test PUBLIC "CATCH_CONFIG_MAIN" "CATCH_CONFIG_COLOUR_NONE")


