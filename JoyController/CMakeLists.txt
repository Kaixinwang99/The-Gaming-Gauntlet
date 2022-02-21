cmake_minimum_required(VERSION 3.0.0)
project(JoyController VERSION 0.1.0)

# find_package(GTest)
# include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(JoyController main.cpp)

add_subdirectory(JoyLib)


target_include_directories(${PROJECT_NAME} PUBLIC JoyLib)

target_link_libraries(${PROJECT_NAME} JoyLib)

add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
