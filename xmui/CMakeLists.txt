cmake_minimum_required(VERSION 3.10)

project(xmui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADER_FILES "include/*.h" "backend/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "backend/*.cpp")
file(GLOB_RECURSE BACKEND_SOURCE_FILES "backend/*.cpp")
file(GLOB_RECURSE BACKEND_HEADER_FILES "backend/*.h")

set(BACKEND_DIRECT2D 1)
set(BACKEND_BLEND2D  2)


if(NOT DEFINED BACKEND_TYPE)
set(BACKEND_TYPE ${BACKEND_DIRECT2D})
endif()


set(PROJECT_LINK_LIBRARIES 
	"wbemuuid"
	"winmm"
)



if(BACKEND_TYPE EQUAL BACKEND_DIRECT2D)
	add_definitions(-DXMUI_USE_DIRECT2D_BACKEND)
	list(APPEND PROJECT_LINK_LIBRARIES "d2d1" "DWrite")
	message("Current backend: Direct2D")
elseif(BACKEND_TYPE EQUAL BACKEND_BLEND2D)
	add_definitions(-DXMUI_USE_BLEND2D_BACKEND)
	list(APPEND PROJECT_LINK_LIBRARIES "blend2d")
	message("Current backend: Blend2D")
endif()


if(MSVC)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")  # 最低警告等级
	
	# add_definitions(-D_CRT_SECURE_NO_WARNINGS -DXMUI_EXPORT -DXMUI_USE_DIRECT2D_BACKEND)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -DXMUI_EXPORT -DUNICODE -D_UNICODE)


	# 替换为静态运行库
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

	vs_file_filter("${HEADER_FILES}" "include" "Header Files")
	vs_file_filter("${SOURCE_FILES}" "src" "Source Files")
	vs_file_filter_unremoved("${BACKEND_SOURCE_FILES}" "backend" "Source Files")
	vs_file_filter_unremoved("${BACKEND_HEADER_FILES}" "backend" "Header Files")

	list(APPEND SOURCE_FILES ${BACKEND_SOURCE_FILES})
	list(APPEND HEADER_FILES ${BACKEND_HEADER_FILES})
endif(MSVC)

include_directories(
	"include"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	# "${CMAKE_SOURCE_DIR}/thirdparty/tgfx/include"
	"${CMAKE_SOURCE_DIR}/thirdparty/blend2d/include"
)

# message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}/thirdparty/blend2d/include")

# add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${PROJECT_HEADERS} ${RCC_FILES})
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_link_directories(${PROJECT_NAME} PRIVATE
	# debug "${CMAKE_SOURCE_DIR}/thirdparty/tgfx/lib/Debug"
	# optimized "${CMAKE_SOURCE_DIR}/thirdparty/tgfx/lib/Release"
	debug "${CMAKE_SOURCE_DIR}/thirdparty/blend2d/lib/Debug"
	optimized "${CMAKE_SOURCE_DIR}/thirdparty/blend2d/lib/Release"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${PROJECT_LINK_LIBRARIES}
)
