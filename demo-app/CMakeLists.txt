cmake_minimum_required(VERSION 3.10)

project(demo_app)

file(GLOB SOURCES "source/*.cpp")
add_executable(demo_app ${SOURCES} "include/GameObject.h"  "source/GameObject.cpp" )

target_link_libraries(demo_app PRIVATE render_api)
target_include_directories(demo_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../render-api/include include/)