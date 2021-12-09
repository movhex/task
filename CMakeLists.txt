cmake_minimum_required(VERSION 3.16.0)

project(task)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME})

set(SRC_FILES
    src/generator.cpp
    src/object.cpp
    src/sorter.cpp
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    src
)

target_sources(${PROJECT_NAME}
PRIVATE
    src/main.cpp
    ${SRC_FILES}
)

target_compile_options(${PROJECT_NAME}
PRIVATE
    -Wall
    -Wextra
    -Wuninitialized
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if (NOT CMAKE_BUILD_TYPE)
    set (build_type release)
else()
    string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
endif()

if (build_type STREQUAL debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g3 -O0 -ggdb3)
elseif (build_type STREQUAL release)
    target_compile_options(${PROJECT_NAME} PRIVATE -g0 -O3)
endif()

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_REQUIRED_LIBRARIES}
)

enable_testing()

add_subdirectory(test)
