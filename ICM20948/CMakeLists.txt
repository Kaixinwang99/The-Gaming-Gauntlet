cmake_minimum_required(VERSION 3.0.0)
project(ICM20948 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ICM20948 main.cpp)

add_subdirectory(rpi_ICM20948)


target_include_directories(${PROJECT_NAME} PUBLIC rpi_ICM20948)
target_link_libraries(${PROJECT_NAME} icm20948)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
