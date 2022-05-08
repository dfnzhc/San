function(add_lib)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs FILES LIBS DEFINITIONS INCLUDEDIRS)

    cmake_parse_arguments(TARGET "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    message(STATUS "${TARGET_NAME} `${TARGET_FILES}` `${TARGET_LIBS}` - BUILD")

    project(${TARGET_NAME} LANGUAGES C CXX)

    source_group("${PROJECT_NAME}\\" FILES ${TARGET_FILES})
    set_source_files_properties(${TARGET_FILES} PROPERTIES LANGUAGE CXX)
    
    add_library(${PROJECT_NAME} STATIC ${TARGET_FILES})

    target_compile_definitions(${PROJECT_NAME} PUBLIC ${TARGET_DEFINITIONS})

    target_include_directories(${PROJECT_NAME} PUBLIC
            ${TARGET_INCLUDEDIRS} 
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}
            )

    target_link_libraries(${PROJECT_NAME} PUBLIC ${TARGET_LIBS})
    target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../pch.hpp)
    
    if (${YUAN_WARNING_AS_ERROR})
        message(STATUS "Warnings as Errors Enabled")
        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
        elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
            target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)
        endif ()
    endif ()
endfunction(add_lib)