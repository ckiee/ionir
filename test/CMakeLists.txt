cmake_minimum_required(VERSION 3.13.1)

enable_testing()

find_package(GTest REQUIRED
    PATHS "googletest" 
)

set(PROJECT_NAME IonIrTests)

set(SOURCES
    stream.cpp
    lexer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main)

add_test(AllTestsInFoo ${PROJECT_NAME})
