cmake_minimum_required(VERSION 3.10)

project(PurLong)

# Устанавливаем версию языка C++17
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)

add_executable(autoTests 
src/purlong.cpp 
src/purmath.cpp
tests/mainTest.cpp 
tests/comparisionsTest.cpp 
tests/arithmeticOperationsTest.cpp
tests/representationTest.cpp)