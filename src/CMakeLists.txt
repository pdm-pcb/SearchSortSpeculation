file(
    GLOB source CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

add_executable(sss ${source})

target_include_directories(
    sss PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}/include"
)

if(NOT CMAKE_BUILD_TYPE)
    message("Defaulting to debug build")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set_target_properties(
    sss PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED on
    CXX_EXTENSIONS off
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
)

list(APPEND default_flags "-Wall" "-Wextra")

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    target_compile_options(
        sss PRIVATE
        ${default_flags} -ggdb3
    )
elseif(${CMAKE_BUILD_TYPE} MATCHES Release)
    target_compile_options(
        sss PRIVATE
        ${default_flags} -O2
    )
endif()


