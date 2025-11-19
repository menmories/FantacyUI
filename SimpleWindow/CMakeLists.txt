cmake_minimum_required(VERSION 3.10)

project(SimpleWindow LANGUAGES CXX)
#set(PROJECT_NAME kplayer)

set(CMAKE_CXX_STANDARD 11)
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
    ${CMAKE_SOURCE_DIR}/FantacyUI/include
)

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCE} ${PROJECT_HEADERS} ${RCC_FILES})
# 设置入口点为mainCRTStartup
set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "/ENTRY:mainCRTStartup"
)

target_link_directories(${PROJECT_NAME} PRIVATE

)

target_link_libraries(${PROJECT_NAME} PRIVATE
    debug ${CMAKE_SOURCE_DIR}/build/lib/Debug/FantacyUI.lib
    optimized ${CMAKE_SOURCE_DIR}/build/lib/Release/FantacyUI.lib
)

