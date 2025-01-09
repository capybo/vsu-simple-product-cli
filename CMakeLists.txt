cmake_minimum_required(VERSION 3.30)
project(simple-product-cli)

set(CMAKE_CXX_STANDARD 20)

add_executable(application main.cpp
        product.h
        file_reader.h
        file_reader.cpp)
