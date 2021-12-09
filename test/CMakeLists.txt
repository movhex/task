project(tests)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
PRIVATE
    ../src
)

list(TRANSFORM SRC_FILES PREPEND "../")

target_sources(${PROJECT_NAME}
PRIVATE
    ${SRC_FILES}
    tests.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES}
)

add_test(NAME Test1 COMMAND tests)
