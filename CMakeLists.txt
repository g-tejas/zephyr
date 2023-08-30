cmake_minimum_required(VERSION 3.16)
project(zephyr 
	LANGUAGES CXX
	DESCRIPTION "Blazingly fast async IO event loop framework")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines -Wall -O2 -D_GNU_SOURCE")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_library(zephyr SHARED src/*.cc)
target_link_libraries(zephyr PRIVATE uring)

file(GLOB EXAMPLE_SRCS examples/*.cc)
foreach(EXAMPLE_SRC ${EXAMPLE_SRCS})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SRC} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE uring zephyr)
endforeach()
