file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        )

add_lib(
        NAME utils
        FILES ${SOURCE_FILES}
        LIBS base
        DEFINITIONS ${SAN_DEFINITIONS}
        INCLUDEDIRS ${SAN_INCLUDES}
)

set_property(TARGET utils PROPERTY FOLDER "San")
