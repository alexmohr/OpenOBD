cmake_minimum_required(VERSION 3.12)
project(open_obd2)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(open_obd2 src/main.cpp src/Config.cpp src/Config.h
        lib/easylogging++.cc)