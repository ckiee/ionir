cmake_minimum_required(VERSION 3.13.1)

set(PROJECT_NAME IonIrTests)

set(SOURCES
    stream.cpp
    lexer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest_main
    Example
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
