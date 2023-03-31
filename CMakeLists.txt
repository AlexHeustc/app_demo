cmake_minimum_required(VERSION 3.23)
project(app_demo C)

# 设置C编译器为gcc
set(CMAKE_C_COMPILER arm-buildroot-linux-gnueabihf-gcc)
set(CMAKE_C_STANDARD 11)

add_executable(app_demo
        Sources/main.c
        Sources/display_manage.c
        Headers/display_manage.h
        Sources/framebuffer.c
        Headers/fontdata.h)
