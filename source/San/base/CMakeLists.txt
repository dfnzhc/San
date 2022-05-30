
file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        )

add_lib(
        NAME base
        FILES ${SOURCE_FILES}
        LIBS spdlog
        DEFINITIONS ${SAN_DEFINITIONS}
        INCLUDEDIRS ${SAN_INCLUDES}
)

set_property(TARGET base PROPERTY FOLDER "San")
