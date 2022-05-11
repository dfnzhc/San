
file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        )

add_lib(
        NAME base
        FILES ${SOURCE_FILES}
        LIBS spdlog
        DEFINITIONS ${YUAN_DEFINITIONS}
        INCLUDEDIRS ${YUAN_INCLUDES}
)

set_property(TARGET base PROPERTY FOLDER "yuan")
