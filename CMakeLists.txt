cmake_minimum_required(VERSION 3.15)
project(PSZT_MemeticAlgorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -O2)

add_executable(PSZT_MemeticAlgorithm
        src/main.cpp src/memetic.cpp src/population.cpp src/specimen.cpp)
