cmake_minimum_required (VERSION 3.17.3 FATAL_ERROR)

include(CMakePrintHelpers)

# This will set the cmake var PROJECT_NAME when called
project(GraphicsSelfStudy_CMakeTest
    LANGUAGES CXX C
    )

# Set CXX Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to Release build type
# Honored when running make -j8 or whatever on the cmd line. Not when building in msvc
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
# Manual message example:
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# # C/++ configuration
# cmake_print_variables(CMAKE_C_FLAGS_DEBUG)
# cmake_print_variables(CMAKE_C_FLAGS_RELEASE)
# cmake_print_variables(CMAKE_C_FLAGS_RELWITHDEBINFO)
# cmake_print_variables(CMAKE_C_FLAGS_MINSIZEREL)
# cmake_print_variables(CMAKE_CXX_FLAGS_DEBUG)
# cmake_print_variables(CMAKE_CXX_FLAGS_RELEASE)
# cmake_print_variables(CMAKE_CXX_FLAGS_RELWITHDEBINFO)
# cmake_print_variables(CMAKE_CXX_FLAGS_MINSIZEREL)

# Note: Can I move this to the dependencies cmakelists???
find_package(OpenGL REQUIRED)
cmake_print_variables(OPENGL_LIBRARIES)
cmake_print_variables(OPENGL_INCLUDE_DIRS)

add_subdirectory(dependencies)

#############################################################
########################   IMGUI   ##########################
#############################################################
# If this doesn't work just add to project sources
set(IMGUI_FILE_DIR "${PROJECT_SOURCE_DIR}/dependencies/imgui-files")
file(GLOB IMGUI_SOURCES
    ${IMGUI_FILE_DIR}/*.h
    ${IMGUI_FILE_DIR}/*.cpp
    )

#############################################################
################### PROJECT SOURCES #########################
#############################################################
list(APPEND PROJECT_SOURCES
    src/main.cpp
    ${IMGUI_SOURCES}
    )
source_group("src" FILES  ${PROJECT_SOURCES})
source_group("imgui" FILES ${IMGUI_SOURCES})

#############################################################
################### PROJECT SHADERS #########################
#############################################################
# TODO: specify them so cmake knows to re-run if we add one
# glob can't detect
file(GLOB_RECURSE SHADERS_PROJECT ./src/shaders/*.glsl)
source_group("shaders" FILES  ${SHADERS_PROJECT})

#############################################################
################## PROJECT EXE/LINK #########################
#############################################################
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
# NOTE: for explictly setting dlls includes see (definitely the first one):
# https://stackoverflow.com/questions/58870951/how-do-i-link-a-library-using-cmake?noredirect=1&lq=1
# https://stackoverflow.com/questions/54039533/cmake-define-dlls-directory-or-files-for-a-generated-project?noredirect=1&lq=1

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    glad
    glfw
    glm
    assimp # NOTE: consider using the precompiled stuff (simliar to what freetype is doing) since this thing is large
    soil2
    freetype # Using the old raw stuff since interface changed
    # gli # NOTE: in gli CMakeLists.txt I commented the add_subdirectory(test)
    )

# NOTE: don't need to include in some cases if the libs CMakeLists was done correctly
target_include_directories(${PROJECT_NAME}
    PRIVATE
        # NOTE: opengl has no headers, that's what glew, gl3w, glad are for.
        glad
        glfw
        glm
        assimp
        # gli
    )

# Copy some dll,lib to the build dirs
get_target_property(FREETYPE_DLL freetype IMPORTED_LOCATION)
get_target_property(FREETYPE_LIB freetype IMPORTED_IMPLIB)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FREETYPE_LIB} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FREETYPE_DLL} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
