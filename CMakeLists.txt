cmake_minimum_required(VERSION 3.10)
project(quxer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 --std=c99 -Wall -Wno-unused-variable")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/include
)

file(GLOB SRCS
    "${PROJECT_SOURCE_DIR}/src/main.c"
    "${PROJECT_SOURCE_DIR}/src/utils/*.c"
    "${PROJECT_SOURCE_DIR}/src/templates/*.c"
    "${PROJECT_SOURCE_DIR}/src/peg/*.c"
    "${PROJECT_SOURCE_DIR}/lib/src/*.c"
)

if ("${CMAKE_C_FLAGS}" MATCHES "-DBOOTSTRAP")
    list(REMOVE_ITEM SRCS
        "${PROJECT_SOURCE_DIR}/src/peg/parser.c"
        "${PROJECT_SOURCE_DIR}/src/peg/ast.c"
        "${PROJECT_SOURCE_DIR}/shared/src/internal.c"
        "${PROJECT_SOURCE_DIR}/shared/src/arena.c"
    )
endif()

add_executable(${PROJECT_NAME}  ${SRCS})

