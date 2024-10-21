cmake_minimum_required(VERSION 3.10)
project(render_api)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

if(WIN32)
	add_library(render_api STATIC
			include/core/AppModel.h
			include/core/Renderer.h
			include/util/Scene.h
			source/AppModel.cpp
			source/Renderer.cpp
			source/Scene.cpp
			source/ConsoleLog.cpp)
else()
	add_library(render_api SHARED
			include/core/AppModel.h
			include/core/Renderer.h
			include/util/Scene.h
			source/AppModel.cpp
			source/Renderer.cpp
			source/Scene.cpp
			include/util/ConsoleLog.h
			source/ConsoleLog.cpp)
endif()

target_include_directories(render_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(render_api PUBLIC glfw)
target_link_libraries(render_api PUBLIC Vulkan::Vulkan)