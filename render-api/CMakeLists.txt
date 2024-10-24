cmake_minimum_required(VERSION 3.10)
project(render_api)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(vk-bootstrap)

set(CMAKE_CXX_STANDARD 23)
set(SOURCES include/core/AppModel.h
		include/core/Renderer.h
		include/util/Scene.h
		source/core/AppModel.cpp
		source/core/Renderer.cpp
		source/util/Scene.cpp
		source/util/ConsoleLog.cpp
		source/util/VkBootstrap.cpp
		source/resource/Buffer.cpp
		include/resource/Buffer.h
		source/resource/Shader.cpp
		include/resource/Shader.h)

if(WIN32)
	add_library(render_api STATIC ${SOURCES} "include/core/Pipeline.h" "source/core/Pipeline.cpp")
else()
	add_library(render_api SHARED ${SOURCES})
endif()

target_include_directories(render_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(render_api PUBLIC glfw)
target_link_libraries(render_api PUBLIC Vulkan::Vulkan vk-bootstrap::vk-bootstrap vk-bootstrap::vk-bootstrap-compiler-warnings)

add_compile_options(-Wunused-parameter)