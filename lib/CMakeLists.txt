cmake_minimum_required(VERSION 3.9)

project(library)

set (DIR_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (DIR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)


set (library_src 
    ${DIR_SRC}/Converters.cpp
)

add_library(${PROJECT_NAME} STATIC ${library_src})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_BINARY_DIR}
        ${DIR_SRC}
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${DIR_INCLUDE}>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


