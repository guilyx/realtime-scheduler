cmake_minimum_required(VERSION 3.10)
project(realtime_scheduler)
set(CMAKE_CXX_STANDARD 14)
set(fper)

include_directories(include)
file(GLOB SOURCES src/*.cpp)

add_executable(rt_sched ${SOURCES})