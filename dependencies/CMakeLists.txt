#############################################################
########################  GLAD  #############################
#############################################################
add_subdirectory( glad )

#############################################################
########################  GLFW  #############################
#############################################################
set( GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )
add_subdirectory( glfw )

#############################################################
########################   GLM  #############################
#############################################################
add_subdirectory( glm )

#############################################################
########################    GLI  ############################
#############################################################
add_subdirectory( gli )

#############################################################
########################  ASSIMP  ###########################
#############################################################
set( ASSIMP_BUILD_ZLIB ON )
set( ASSIMP_BUILD_TESTS OFF)
set( ASSIMP_BUILD_ASSIMP_TOOLS OFF)
add_subdirectory( assimp )
# Assimp throws warnings as error for somethings when using 17
set_property(TARGET assimp PROPERTY CXX_STANDARD 14)

#############################################################
########################  FREETYPE  #########################
#############################################################
# NOTE: Interface changed a bit, might want to hold off and just use the raw one I have
# see https://github.com/winlibs/freetype
# add_subdirectory( freetype )
# Precompiled version, we copy the dll and lib in POST_BUILD. See root cmakelists.
add_library(freetype SHARED IMPORTED GLOBAL)
set(FREETYPE_DLL "${CMAKE_CURRENT_SOURCE_DIR}/freetype/x64/freetype.dll")
set(FREETYPE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/freetype/x64/freetype.lib")
set_target_properties(freetype PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(freetype PROPERTIES IMPORTED_LOCATION ${FREETYPE_DLL})
set_target_properties(freetype PROPERTIES IMPORTED_IMPLIB ${FREETYPE_LIB})

#############################################################
########################   SOIL2   ##########################
#############################################################
set(SOIL2_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/soil2/src")
file(GLOB_RECURSE SOIL2_SOURCES
    ${SOIL2_SOURCE_DIR}/common/*.hpp
    ${SOIL2_SOURCE_DIR}/common/*.cpp
    ${SOIL2_SOURCE_DIR}/SOIL2/*.h
    ${SOIL2_SOURCE_DIR}/SOIL2/*.c
    )
# NOTE: MUST be STATIC
add_library(soil2 STATIC ${SOIL2_SOURCES})
# NOTE: This will allow you to just put soil2 in the link library list and not have to put it in the include list
set_target_properties(soil2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${SOIL2_SOURCE_DIR}/SOIL2")
