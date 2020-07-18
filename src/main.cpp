

// // #include "gli/save_dds.hpp"
// // #include "gli/texture_cube_array.hpp"
// // #include <gli/gli.hpp>
// // GLuint CreateTexture(char const* Filename)
// // {
// //     gli::texture Texture = gli::load(Filename);
// //     if(Texture.empty())
// //         return 0;
// //
// //     gli::gl GL(gli::gl::PROFILE_GL33);
// //     gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
// //     GLenum Target = GL.translate(Texture.target());
// //     assert(gli::is_compressed(Texture.format()) && Target == gli::TARGET_2D);
// //
// //     GLuint TextureName = 0;
// //     glGenTextures(1, &TextureName);
// //     glBindTexture(Target, TextureName);
// //     glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
// //     glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
// //     glTexParameteriv(Target, GL_TEXTURE_SWIZZLE_RGBA, &Format.Swizzles[0]);
// //     glTexStorage2D(Target, static_cast<GLint>(Texture.levels()), Format.Internal, Extent.x, Extent.y);
// //     for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
// //     {
// //         glm::tvec3<GLsizei> Extent(Texture.extent(Level));
// //         glCompressedTexSubImage2D(
// //             Target, static_cast<GLint>(Level), 0, 0, Extent.x, Extent.y,
// //             Format.Internal, static_cast<GLsizei>(Texture.size(Level)), Texture.data(0, 0, Level));
// //     }
// //
// //     return TextureName;
// // }
// #include <gli/texture2d.hpp>
// #include <gli/convert.hpp>
// #include <gli/generate_mipmaps.hpp>
// #include <gli/load.hpp>
// #include <gli/save.hpp>
// bool convert_rgb32f_rgb9e5(char const* FilenameSrc, char const* FilenameDst)
// {
//     if(FilenameDst == nullptr)
//         return false;
//     if(std::strstr(FilenameDst, ".dds") != nullptr || std::strstr(FilenameDst, ".ktx") != nullptr)
//         return false;
//     gli::texture2d TextureSource(gli::load(FilenameSrc));
//     if(TextureSource.empty())
//         return false;
//     if(TextureSource.format() != gli::FORMAT_RGB16_SFLOAT_PACK16 && TextureSource.format() != gli::FORMAT_RGB32_SFLOAT_PACK32)
//         return false;
//     gli::texture2d TextureMipmaped = gli::generate_mipmaps(TextureSource, gli::FILTER_LINEAR);
//     gli::texture2d TextureConverted = gli::convert(TextureMipmaped, gli::FORMAT_RGB9E5_UFLOAT_PACK32);
//     gli::save(TextureConverted, FilenameDst);
//     return true;
// }
// int main()
// {
//     GLFWwindow* window;
//
//     // Initialize the library
//     if (!glfwInit())
//     {
//         return -1;
//     }
//
//     // Create a windowed mode window and its OpenGL context
//     window = glfwCreateWindow(640, 480, "GLFW CMake starter", NULL, NULL);
//     if (!window)
//     {
//         glfwTerminate();
//         return -1;
//     }
//
//     // Make the window's context current
//     glfwMakeContextCurrent(window);
//     const glm::vec4 color{ 0.4f, 0.3f, 0.4f, 0.0f  };
//     glClearColor(color.r, color.g, color.b, color.a);
//
//     // Loop until the user closes the window
//     while (!glfwWindowShouldClose(window))
//     {
//         // Render here */
//         glClear(GL_COLOR_BUFFER_BIT);
//
//         // Swap front and back buffers
//         glfwSwapBuffers(window);
//
//         // Poll for and process events
//         glfwPollEvents();
//     }
//
//     glfwTerminate();
//     return 0;
// }


#include <iostream>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

// This example is taken from https://learnopengl.com/
// https://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
// The code originally used GLEW, I replaced it with Glad

// Compile:
// g++ example/c++/hellowindow2.cpp -Ibuild/include build/src/glad.c -lglfw -ldl


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        const glm::vec4 color{ 0.4f, 0.3f, 0.4f, 1.0f };
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

// #include <stdio.h>
// // ft2build.h has to go in dependencies root folder because of how freetype does its thing.
// // #include <ft2build.h>
// // #include FT_FREETYPE_H
// // #include <SOIL2.h>
// int main()
// {
//     // FT_Library ft;
//     // if (FT_Init_FreeType(&ft)) // All functions return a value different than 0 whenever an error occurred
//     printf("\nJAWN %g", 1.0f); // %g is shortest way to print the value stored
//     return 0;
// }
