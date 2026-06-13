cmake_minimum_required(VERSION 3.10)

project(skiademo)
#set(PROJECT_NAME kplayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_definitions(-D _CRT_SECURE_NO_WARNINGS)

set(PROJECT_HEADERS

)

set(PROJECT_SOURCE 
    "src/main.cpp"

)

if(MSVC)
    foreach(header ${PROJECT_HEADERS})
        string(REGEX REPLACE "/[^/]*$" "" file_filter ${header})
        string(REPLACE "include" "" file_group_path ${file_filter})
        source_group("Header Files/${file_group_path}" FILES "${header}")
        # message("header_filter=${file_filter}")
    endforeach()

    foreach(source ${PROJECT_SOURCE})
        string(REGEX REPLACE "/[^/]*$" "" file_filter ${source})
        string(REPLACE "src" "" file_group_path ${file_filter})
        source_group("Source Files/${file_group_path}" FILES "${source}")
        # message("source_file_filter=${file_filter}")
    endforeach()
endif(MSVC)

include_directories(
    "include"
    E:/Libs/skia/Skia-m138-80d088a-1-windows-Release-x64
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${PROJECT_HEADERS} ${RCC_FILES})
# 设置入口点为mainCRTStartup
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     LINK_FLAGS "/ENTRY:mainCRTStartup"
# )

target_link_directories(${PROJECT_NAME} PRIVATE
    debug E:/Libs/skia/Skia-m138-80d088a-1-windows-Debug-x64/out/Debug-windows-x64
    optimized E:/Libs/skia/Skia-m138-80d088a-1-windows-Release-x64/out/Release-windows-x64
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    skia.lib
)

