cmake_minimum_required(VERSION 3.5)

project(threadpool_test LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "D:\\Qt\\Qt5.14.2\\5.14.2\\msvc2017_64")# 不设置此路径可能会导致 error LNK2019: 无法解析的外部符号

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(threadpool_test
  main.cpp
)
target_link_libraries(threadpool_test Qt5::Core)
