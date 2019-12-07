cmake_minimum_required(VERSION 3.10)
project(quxer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c99 -Wall -Wno-unused-variable")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/shared/include
)

file(GLOB SRCS
    "${PROJECT_SOURCE_DIR}/src/main.c"
    "${PROJECT_SOURCE_DIR}/src/utils/*.c"
    "${PROJECT_SOURCE_DIR}/src/templates/*.c"
    "${PROJECT_SOURCE_DIR}/src/peg/*.c"
    "${PROJECT_SOURCE_DIR}/shared/src/*.c"

)

add_executable(${PROJECT_NAME}  ${SRCS})

