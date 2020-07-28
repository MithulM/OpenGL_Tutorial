#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#define NUM_TRIANGLE_VERTEX 3
#define ASSERT(x) if (!(x)) __debugbreak();

#ifdef _DEBUG
    #define GLError(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
    #define GLError(x) x
#endif


static void GLClearError()
{
    while (glGetError());
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]: (0x" << std::hex << error << ")\n\ton line: " << std::dec << line << "\n\tby function: " << function << "\n\tin file: " << file << std::endl << std::endl;
        return false;
    }
    return true;
}

static unsigned int createShader(std::string type, std::string mode = "default")
{
    std::ifstream t(type + "_" + mode + ".shader");
    std::string temp((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());

    const char* shaderSource = temp.c_str();
    // making a new shader object
    unsigned int shaderID = glCreateShader((type == "fragment") ? GL_FRAGMENT_SHADER : (type == "vertex") ? GL_VERTEX_SHADER : GL_GEOMETRY_SHADER);
    // Binding the source to shader
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    // Compiling shader source
    glCompileShader(shaderID);

    // Checking for errors
    int  success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "[OpenGL Error]: " + type + " shader compilation failed\n" << infoLog << std::endl;
    }

    return shaderID;
}