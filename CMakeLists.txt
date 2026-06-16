cmake_minimum_required(VERSION 3.10)

project(xmui)
#set(PROJECT_NAME kplayer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


function(vs_file_filter files replacedName vsFilterName)
    foreach(aFile ${files})
        string(REGEX REPLACE "/[^/]*$" "" file_filter ${aFile})
        string(REGEX REPLACE ".*${replacedName}" "" file_group_path ${file_filter})
        source_group("${vsFilterName}/${file_group_path}" FILES "${aFile}")
        # message("source_group1=${vsFilterName}/${file_group_path}")
        # message("file_filter=${aFile}")
        # message("file_group_path=${file_group_path}")
        # message("replacedName=${replacedName}")
    endforeach()
endfunction()

function(vs_file_filter_unremoved files replacedName vsFilterName)
    foreach(aFile ${files})
        string(REGEX REPLACE "/[^/]*$" "" file_filter ${aFile})
        string(REGEX REPLACE ".*${replacedName}" "" file_group_path ${file_filter})
        string(PREPEND file_group_path "${replacedName}")
        string(REPLACE "/" "\\" file_group "${vsFilterName}//${file_group_path}")
        source_group("${file_group}" FILES "${aFile}")
        # message("file_filter=${aFile}")
        # message("file_group_path=${file_group_path}")
        # message("replacedName=${replacedName}")
        message("${file_group}")
    endforeach()
endfunction()

# 设置输出目录，确保库和可执行文件在同一目录，便于运行
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


add_subdirectory(simplewindow)
add_subdirectory(xmui)
add_subdirectory(skiademo)
add_subdirectory(thorvgdemo)


message("${CMAKE_CURRENT_SOURCE_DIR}")
# 在VS中设置为启动项目
# set_property(DIRECTORY ${CMAKE_SOURCE_DIR}/SimpleWindow PROPERTY VS_STARTUP_PROJECT SimpleWindow)
# set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SimpleWindow)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT simplewindow)
