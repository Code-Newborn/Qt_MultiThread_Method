cmake_minimum_required(VERSION 3.5)

project(threadpool LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "D:\\Qt\\Qt5.14.2\\5.14.2\\msvc2017_64")# 不设置此路径可能会导致 error LNK2019: 无法解析的外部符号

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

#引入Qt库
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5SerialPort REQUIRED)
FIND_PACKAGE(Qt5PrintSupport REQUIRED)
# FIND_PACKAGE(Qt5Sql REQUIRED)
# FIND_PACKAGE(Qt5Network REQUIRED)
# FIND_PACKAGE(Qt5Concurrent REQUIRED)

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

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # 指定.exe文件输出路径为CmakeList.txt所在目录，是其他文件相对路径的参考，不可删除

# 包含头文件路径，需为根目录
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR} # 包含当前处理的 CMakeLists.txt 文件所在的路径

  )

#启用qrc资源文件
# QT5_ADD_RESOURCES(RES_FILES resource/resource.qrc)

file(GLOB SRC_FILES
  *.cpp
  )
file(GLOB HEADER_FILES
  ./*.h
)
file(GLOB FORMS
  ./*.ui
)
file(GLOB RESOURCE_FILES
  ./*.qrc
)
# file(GLOB PYLON_LIBS
#   ./lib/pylon_libs/x64/*.lib
# )

add_executable(${PROJECT_NAME}
  ${SRC_FILES}
  ${HEADER_FILES}
  ${FORMS}
  ${RESOURCE_FILES}
)

# 链接 目标和其依赖项所要使用的库。
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ) # 需要将D:\OpenCV-4.5.0-withContribNonfree-MinGW730-Qt\x64\mingw\bin加入环境变量path
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::SerialPort Qt5::Gui Qt5::PrintSupport) # 链接Qt库
