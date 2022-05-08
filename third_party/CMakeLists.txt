cmake_minimum_required(VERSION 3.21)

project(third_party LANGUAGES C CXX)

# spdlog
add_subdirectory(spdlog)
set_property(TARGET spdlog PROPERTY FOLDER "ThirdParty")
set(YUAN_INCLUDES ${YUAN_INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include" PARENT_SCOPE)
