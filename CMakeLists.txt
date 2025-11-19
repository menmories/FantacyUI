cmake_minimum_required(VERSION 3.10)

project(FantacyUI)
#set(PROJECT_NAME kplayer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 设置输出目录，确保库和可执行文件在同一目录，便于运行
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(FantacyUI)
add_subdirectory(SimpleWindow)
add_subdirectory(FramelessWindow)

message("${CMAKE_CURRENT_SOURCE_DIR}")
# 在VS中设置为启动项目
# set_property(DIRECTORY ${CMAKE_SOURCE_DIR}/SimpleWindow PROPERTY VS_STARTUP_PROJECT SimpleWindow)
# set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SimpleWindow)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SimpleWindow)
