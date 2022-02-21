cmake_minimum_required(VERSION 3.0.0)
project(JoyTest VERSION 0.1.0)



find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} JoyTest.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../JoyLib)



target_link_libraries(${PROJECT_NAME} PRIVATE JoyLib gtest pthread)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)