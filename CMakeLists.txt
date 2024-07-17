cmake_minimum_required(VERSION 3.17)
project(srt2ass)


set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(srt2ass
    main.cpp
    SRTReader.h
    SRTReader.cpp
)
