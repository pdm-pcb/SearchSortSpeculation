cmake_minimum_required(VERSION 3.19)

project(SearchSortSpeculation VERSION 0.01)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
    ${PROJECT_SOURCE_DIR}/include/CMakeConfig.hpp.in
    "${PROJECT_BINARY_DIR}/include/CMakeConfig.hpp"
)

ADD_CUSTOM_TARGET(
    Debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Creating the executable in the debug mode."
)

ADD_CUSTOM_TARGET(
    Release
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Creating the executable in the release mode."
)

add_subdirectory("src/")
