cmake_minimum_required(VERSION 3.21)

# set the name of project
project(San)

# add the path of local cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# remember replace XXX to the proper name
include(Global_Options)
# some util functions and macros
include(utils)

list(APPEND SAN_DEFINITIONS)

set(SAN_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/source/")

# add third party libraries
add_subdirectory(third_party)

# add the library
add_subdirectory(source)

if(SAN_BUILD_TESTS)
    # add tests
    add_subdirectory(tests)
endif()