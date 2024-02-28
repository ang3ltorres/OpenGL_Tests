cmake_minimum_required(VERSION 3.3)

set(CMAKE_C_STANDARD 99)

project(plutosvg C)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(PLUTOSVG_SOURCE
    source/plutosvg.c
    source/plutosvg.h
)

add_library(plutosvg STATIC ${PLUTOSVG_SOURCE})

add_subdirectory(plutovg)

target_include_directories(plutosvg PUBLIC source)
target_link_libraries(plutosvg PUBLIC plutovg)
