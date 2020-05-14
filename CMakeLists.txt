cmake_minimum_required(VERSION 3.16)
project(cpp_vm)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_vm main.cpp stack.cpp stack.h context.cpp context.h operation.cpp operation.h vm_var.cpp vm_var.h op_argument.cpp op_argument.h)