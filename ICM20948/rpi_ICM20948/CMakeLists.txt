cmake_minimum_required(VERSION 3.0.0)
project(libicm20948 VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

set(LIBSRC icm20948.cpp)
set(LIBINCLUDE icm20948.h)

add_library(icm20948
  ${LIBSRC}
)

target_link_libraries(icm20948 pigpio)