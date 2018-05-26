cmake_minimum_required(VERSION 3.10)
project(Final)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Final
        AnimatedRect.cpp
        AnimatedRect.h
        App.cpp
        App.h
        app_main.cpp
        Bullet.cpp
        Bullet.h
        Character.cpp
        Character.h
        GlutApp.cpp
        GlutApp.h
        RgbImage.cpp
        RgbImage.h
        TexRect.cpp
        TexRect.h)
