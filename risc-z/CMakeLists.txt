cmake_minimum_required(VERSION 3.17)
project(RISC-Z)

set(CMAKE_GENERATOR "Unix Makefiles")
set(CMAKE_GENERATOR "Ninja")

set(CMAKE_DEBUG_POSTFIX d)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("debug mode")
    add_compile_definitions(DEBUG)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

if(CMAKE_BUILD_TYPE MATCHES Release)
    message("release mode")
    add_compile_definitions(NDEBUG)
endif(CMAKE_BUILD_TYPE MATCHES Release)

set(SRC_LIST main.c cpu.c memory.c ecall.c)

add_executable(risc-z ${SRC_LIST})
