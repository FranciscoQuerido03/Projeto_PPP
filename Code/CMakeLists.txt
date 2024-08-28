cmake_minimum_required(VERSION 3.22)
project(Projeto_PPP C)

set(CMAKE_C_STANDARD 11)

add_executable(Projeto_PPP main.c listas.c listas.h)
add_compile_options(-Wall -Wextra)
