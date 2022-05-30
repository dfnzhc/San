file(GLOB SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        )

add_lib(
        NAME platform
        FILES ${SOURCE_FILES}
        LIBS base glfw_lib
        DEFINITIONS ${SAN_DEFINITIONS}
        INCLUDEDIRS ${SAN_INCLUDES}
)

set_property(TARGET platform PROPERTY FOLDER "San")
