cmake_minimum_required(VERSION 3.9)

if (CMAKE_VERSION VERSION_LESS "3.9")
  project(CONVERTERS_Tests
    VERSION 1.0.0
    LANGUAGES CXX
  )
else()
  project(CONVERTERS_Tests
      VERSION 1.0.0
      LANGUAGES CXX
      DESCRIPTION "Test tool for Converters library"
  )
endif()

################################################################################
# Library
################################################################################
find_package(GTest REQUIRED)

################################################################################
# Sources
################################################################################
file(GLOB_RECURSE src_cpp *.cpp)
file(GLOB_RECURSE src_h *.h)

add_executable(${PROJECT_NAME} ${src_cpp} ${src_h})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME} 
  PUBLIC
    library
  PRIVATE
    GTest::GTest GTest::Main
)


################################################################################
# Compilation flags
################################################################################
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /Ob2 /Oi /Ot")
  # Включает макрос __cplusplus, чтобы сообщить о поддерживаемом стандарте 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # using GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # using Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-var-template -Wno-switch")

  if (CMAKE_CXX_COMPILER MATCHES ".+clang-cl.+") # using Clang-CL
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /Ob2 /Oi /Ot")
    target_link_libraries(${PROJECT_NAME} libomp.lib)
  else() # using Clang GNU
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
  endif()
endif()