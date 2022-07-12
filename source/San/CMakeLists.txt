cmake_minimum_required(VERSION 3.21)

add_subdirectory(base)
add_subdirectory(platform)
add_subdirectory(utils)

add_library(San INTERFACE)
target_link_libraries(San INTERFACE base platform utils)
target_include_directories(San INTERFACE ${SAN_INCLUDES})

add_library(San::Base ALIAS base)
add_library(San::San ALIAS San)
