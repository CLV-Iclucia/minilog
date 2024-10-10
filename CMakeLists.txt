cmake_minimum_required(VERSION 3.29)
project(minilog)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cc)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(minilog ${SOURCES} ${HEADERS})
target_include_directories(minilog PUBLIC include)

file(GLOB TEST_LIST test/*.cc)
foreach(TEST_FILE ${TEST_LIST})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} minilog)
endforeach()