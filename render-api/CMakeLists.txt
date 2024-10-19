cmake_minimum_required(VERSION 3.10)
project(render_api)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

file(GLOB SOURCES "source/*.cpp")
if(WIN32)
	add_library(render_api STATIC ${SOURCES})
else()
	add_library(render_api SHARED ${SOURCES})
endif()

target_include_directories(render_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(render_api PUBLIC glfw)
target_link_libraries(render_api PUBLIC Vulkan::Vulkan)