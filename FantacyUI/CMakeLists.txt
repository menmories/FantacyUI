cmake_minimum_required(VERSION 3.10)

project(FantacyUI C CXX)
#set(PROJECT_NAME kplayer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_definitions(-D _CRT_SECURE_NO_WARNINGS -D FANTACY_EXPORT)


set(PROJECT_HEADERS
    "include/PlatformDef.h"
    "include/Core/fa_string.h"
    "include/Core/FaString.h"
    "include/Painter/stb_image.h"
    "include/Painter/CPainterDevice.h"
    "include/Painter/CPainter.h"
    "include/Painter/CPixmap.h"
    "include/Painter/CD3D11Device.h"
    "include/Painter/CD3D11Bitmap.h"
    "include/Utils/pugixml.hpp"
    "include/Utils/pugiconfig.hpp"
    "include/Utils/CEvent.h"
    "include/Widgets/CWidget.h"
    "include/Widgets/CLayout.h"
    "include/Widgets/CObject.h"

    "include/Window/CWindow.h"
    "include/CApplication.h"
)

set(PROJECT_SOURCE 
    "src/main.cpp"
    "src/Core/fa_string.cpp"
    "src/Core/FaString.cpp"
    "src/Painter/CPainterDevice.cpp"
    "src/Painter/CPainter.cpp"
    "src/Painter/CPixmap.cpp"
    "src/Painter/CD3D11Device.cpp"
    "src/Painter/CD3D11Bitmap.cpp"
    "src/Utils/pugixml.cpp"
    "src/Utils/CEvent.cpp"
    "src/Widgets/CWidget.cpp"
    "src/Widgets/CLayout.cpp"
    "src/Widgets/CObject.cpp"
    "src/Window/CWindow.cpp"
    "src/CApplication.cpp"
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
)

# add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${PROJECT_HEADERS} ${RCC_FILES})
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE} ${PROJECT_HEADERS})

target_link_directories(${PROJECT_NAME} PRIVATE
    
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Iphlpapi
    ws2_32
    wbemuuid
    gdiplus
    d3d11
    d3dcompiler
    Msimg32
)

