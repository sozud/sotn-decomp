cmake_minimum_required(VERSION 3.12)
project(libclang_example)

set(CMAKE_CXX_STANDARD 11)

# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Find libclang
find_package(Clang REQUIRED)

get_cmake_property(_variableNames VARIABLES)

include_directories(${CLANG_INCLUDE_DIRS})
link_directories(${CLANG_LIBRARY_DIRS})
add_definitions(${CLANG_DEFINITIONS})

# Add your source code file here
set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_library(libclangBasic NAMES clangBasic clang-cpp HINTS ${CLANG_SEARCH})
find_library(libclang-shared libclang-cpp.so HINTS ${CLANG_SEARCH})

foreach(_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()


# Link against libclang
target_link_libraries(${PROJECT_NAME} ${CLANG_LIBRARIES})

# libclang-cpp-dev