# add_subdirectory( glad )
#
# set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
# set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
# add_subdirectory( glfw )
#
# add_subdirectory( glm )
#
# add_subdirectory( gli )
#
# # set( ASSIMP_BUILD_SHARED_LIBS OFF )
# set( ASSIMP_BUILD_ZLIB ON )
# set( ASSIMP_BUILD_TESTS OFF)
# set( ASSIMP_BUILD_ASSIMP_TOOLS OFF)
# add_subdirectory( assimp )
# # Assimp throws warnings as error for somethings when using 17
# # set_target_properties(assimp PROPERTIES CXX_STANDARD 14)
# target_compile_features(assimp PRIVATE cxx_std_14)

# NOTE: Interface changed a bit, might want to hold off and just use the raw one I have
# see https://github.com/winlibs/freetype
# add_subdirectory( freetype )


# file(GLOB_RECURSE SOURCES_FREETYPE
#     ${CMAKE_CURRENT_SOURCE_DIR}/freetype/config/*.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/freetype/*.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/freetype/*.h
#     )
# add_library(freetype
#     STATIC ${SOURCES_FREETYPE}
# )
# # CMake will complain if you don't set this
# set_target_properties(freetype PROPERTIES LINKER_LANGUAGE CXX)

add_library(freetype SHARED IMPORTED GLOBAL)
set(FREETYPE_DLL "${CMAKE_CURRENT_SOURCE_DIR}/freetype/x64/freetype.dll")
set(FREETYPE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/freetype/x64/freetype.lib")
set_target_properties(freetype PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(freetype PROPERTIES IMPORTED_LOCATION ${FREETYPE_DLL})
set_target_properties(freetype PROPERTIES IMPORTED_IMPLIB ${FREETYPE_LIB})

set(SOIL2_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/soil2/src")
file(GLOB_RECURSE SOURCES_SOIL2
    ${SOIL2_SOURCE_DIR}/common/*.cpp
    ${SOIL2_SOURCE_DIR}/common/*.hpp
    ${SOIL2_SOURCE_DIR}/SOIL2/*.c
    ${SOIL2_SOURCE_DIR}/SOIL2/*.h
    )
# NOTE: MUST be STATIC
add_library(soil2
    STATIC ${SOURCES_SOIL2}
)
# NOTE: This will allow you to just put SOIL2 in the link library list and not have to put it in the include list
set_target_properties(soil2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${SOIL2_SOURCE_DIR}/SOIL2")
