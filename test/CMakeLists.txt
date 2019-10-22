cmake_minimum_required(VERSION 3.13.1)

enable_testing()

#find_package(GTest REQUIRED
#    PATHS "../libs/googletest/googletest/generated"
#)

set(PROJECT_NAME IonIrTests)

set(SOURCES
    stream.cpp
    lexer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

#target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main)
target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest_main
    ion_ir
)

# Specify additional include directories to look for imports.
target_include_directories(${PROJECT_NAME} PRIVATE "../src")

# Add tests.
#add_test(AllTestsInFoo ${PROJECT_NAME})
