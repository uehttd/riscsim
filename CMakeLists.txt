cmake_minimum_required(VERSION 3.9)
project(riscsim)

set(CMAKE_CXX_STANDARD 17)

add_executable(riscsim main.cpp rv32i_op.h inst_decode.h inst_decode.c rv32i_op.c)