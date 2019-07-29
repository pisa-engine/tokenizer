cmake_minimum_required(VERSION 3.0)
project(tokenizer CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(TOKENIZER_ENABLE_TESTING "Enable testing of the library." ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()
MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external)

# Add code coverage
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/CMake-codecov/cmake")
find_package(codecov)
list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/external/*'")


include_directories(include)

add_library(tokenizer
    "${PROJECT_SOURCE_DIR}/include/tokenizer/term_tokenizer.hpp"
    "${PROJECT_SOURCE_DIR}/src/term_tokenizer.cpp"
)
target_link_libraries(tokenizer
    Boost::boost
)
target_include_directories(tokenizer PUBLIC
    $<BUILD_INTERFACE:${TOKENIZER_INCLUDE_BUILD_DIR}>
    $<INSTALL_INTERFACE:${TOKENIZER_INCLUDE_INSTALL_DIR}>
)


add_subdirectory(src)

if (TOKENIZER_ENABLE_TESTING AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
