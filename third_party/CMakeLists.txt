cmake_minimum_required(VERSION 3.21)

project(third_party LANGUAGES C CXX)

# spdlog
find_package(spdlog CONFIG REQUIRED)
add_library(spdlog INTERFACE)
target_link_libraries(spdlog INTERFACE spdlog::spdlog_header_only)

# glfw
find_package(glfw3 CONFIG REQUIRED)
add_library(glfw_lib INTERFACE)
target_link_libraries(glfw_lib INTERFACE glfw)