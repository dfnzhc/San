cmake_minimum_required(VERSION 3.21)

add_subdirectory(base)
add_subdirectory(platform)

add_library(Yuan INTERFACE)
target_link_libraries(Yuan INTERFACE base platform)
target_include_directories(Yuan INTERFACE ${YUAN_INCLUDES})

add_library(Yuan::Yuan ALIAS Yuan)