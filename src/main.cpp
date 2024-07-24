#include "initializeWindow.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

// Callback to handle user resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void handleEscKey(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// Read shader source from file
std::string readShaderSource(const char *shaderFile) {
    std::ifstream shaderStream(shaderFile);
    std::stringstream shaderContent;
    shaderContent << shaderStream.rdbuf();
    return shaderContent.str();
}

int main() {
    GLFWwindow *window = initializeWindow();
    if (window == NULL)
        return -1;

    float vertices1[] = {
        -1.0f, -0.5f, 0.0f, -0.1f, -0.5f, 0.0f, -0.5f, 0.25f, 0.0f,
    };

    float vertices2[] = {
        1.0f, -0.5f, 0.0f, 0.1f, -0.5f, 0.0f, 0.5f, 0.25f, 0.0f,
    };

    // bind VAO
    unsigned int VAO1; // Vertex Array Object
    glGenVertexArrays(1, &VAO1);
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO1);
    // copy vertices array in a vertex buffer for OpenGL to use
    unsigned int VBO1; // Vertex Buffer Object
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO2);
    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

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

    // Read fragment shader source from file
    std::string fragmentShaderYellowSource =
        readShaderSource("src/shaders/fragmentShaderYellow.glsl");
    const char *fragmentShaderYellowCode = fragmentShaderYellowSource.c_str();

    unsigned int fragmentShaderYellow;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowCode, NULL);
    glCompileShader(fragmentShaderYellow);

    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS,
                  &shadeCompilationSuccessful);
    if (!shadeCompilationSuccessful) {
        glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMEN::YELLOW::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int shaderProgramYellow;
    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    // Shaders are now loaded and no longer necessary at this point
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShaderYellow);

    int programCompilationSuccessful;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS,
                   &programCompilationSuccessful);
    if (!programCompilationSuccessful) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS,
                   &programCompilationSuccessful);
    if (!programCompilationSuccessful) {
        glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::YELLOW::LINK_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        handleEscKey(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
