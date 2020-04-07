cmake_minimum_required(VERSION 3.15)
project(abc C)

set(CMAKE_C_STANDARD 99)

add_executable(abc main.c)
add_executable(helloworld helloworld.c)
add_executable(typesize typesize.c)
add_executable(r_drive0.c r_drive0.c)
add_executable(where where.c)

add_executable(04-talkback 04/talkback.c)
add_executable(04-define 04/defines.c)
add_executable(04-width 04/width.c)
add_executable(04-floats 04/floats.c)
add_executable(04-flags 04/flags.c)
add_executable(04-stringf 04/stringf.c)
add_executable(04-intconv 04/intconv.c)
add_executable(04-floatcnv 04/floatcnv.c)

add_executable(15-binbit 15/binbit.c)