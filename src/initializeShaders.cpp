#include "initializeShaders.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Read shader source from file
std::string readShaderSource(const char *shaderFile) {
    std::ifstream shaderStream(shaderFile);
    std::stringstream shaderContent;
    shaderContent << shaderStream.rdbuf();
    return shaderContent.str();
}

unsigned int initializeShaders(GLFWwindow *window) {
    // Read vertex shader source from file
    std::string vertexShaderSource =
        readShaderSource("src/shaders/vertexShader.glsl");

    const char *vertexShaderCode = vertexShaderSource.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    int shadeCompilationSuccessful;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shadeCompilationSuccessful);

    if (!shadeCompilationSuccessful) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    // Read fragment shader source from file
    std::string fragmentShaderSource =
        readShaderSource("src/shaders/fragmentShader.glsl");
    const char *fragmentShaderCode = fragmentShaderSource.c_str();

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,
                  &shadeCompilationSuccessful);
    if (!shadeCompilationSuccessful) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Shaders are now loaded and no longer necessary at this point
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int programCompilationSuccessful;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS,
                   &programCompilationSuccessful);
    if (!programCompilationSuccessful) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }
    return shaderProgram;
}
