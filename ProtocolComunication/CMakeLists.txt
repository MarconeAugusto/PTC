cmake_minimum_required(VERSION 3.14)
project(ProtocolComunication)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProtocolComunication main.cpp Serial.cpp Serial.h Framming.cpp Framming.h)