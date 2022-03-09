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

add_library(libicm20948
  SHARED
  ${LIBSRC}
  )

set_target_properties(libicm20948 PROPERTIES
  SOVERSION 1
  PUBLIC_HEADER "${LIBINCLUDE}")

target_link_libraries(libicm20948 pigpio)