cmake_minimum_required(VERSION 3.20)

project(PROJECT_NAME VERSION 0.0.0 LANGUAGES CXX)

set(PROJECT_NAME_MAIN_PROJECT OFF)
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(PROJECT_NAME_MAIN_PROJECT ON)
endif()

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${MPI_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest/googletest/include)

set(PROJECET_NAME_THIRD_LIBRARIES ${MPI_LIBRARIES} OpenMP::OpenMP_CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# add_subdirectory(chapter_01)
# add_subdirectory(chapter_02)
# add_subdirectory(chapter_03)
# add_subdirectory(chapter_04)
# add_subdirectory(chapter_05)
add_subdirectory(src)
enable_testing()
include(GoogleTest)
add_subdirectory(test)
