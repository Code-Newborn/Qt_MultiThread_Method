cmake_minimum_required(VERSION 3.5)

project(Concurrent LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "D:\\Qt\\Qt5.14.2\\5.14.2\\msvc2017_64")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # 指定.exe文件输出路径为CmakeList.txt所在目录，是其他文件相对路径的参考，不可删除

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Concurrent)

#引入Opencv库
find_package(OpenCV
        PATHS D:\\OpenCV-4.5.0-withContribNonfree-VS2022-VScode # 指定第三方Opencv库的OpenCVConfig.cmake所在路径
        NO_DEFAULT_PATH
        REQUIRED)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS}) # 包含Opencv路径
    message( ${OpenCV_LIBS})    # 打印Opencv库Lib模块内容
else()
     message("OpenCV not found, so we won't build the project.")
endif()

add_executable(Concurrent
  main.cpp
)

# 链接 目标和其依赖项所要使用的库。
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ) # 需要将D:\OpenCV-4.5.0-withContribNonfree-MinGW730-Qt\x64\mingw\bin加入环境变量path
target_link_libraries(Concurrent Qt5::Core Qt5::Widgets Qt5::Concurrent)
