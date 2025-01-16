#include "initializeWindow.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void handleEscKey(GLFWwindow *window);
std::string readShaderSource(const char *shaderFile);
void generateAndBindVAO(unsigned int &VAO, unsigned int &VBO, float *vertices, size_t size);
unsigned int compileShader(const char *shaderCode, GLenum shaderType);
unsigned int createShaderProgram(const char *vertexShaderCode, const char *fragmentShaderCode);

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

    float vertices3[] = {
        0.0f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
    };

    unsigned int VAO1, VBO1;
    generateAndBindVAO(VAO1, VBO1, vertices1, sizeof(vertices1));

    unsigned int VAO2, VBO2;
    generateAndBindVAO(VAO2, VBO2, vertices2, sizeof(vertices2));

    unsigned int VAO3, VBO3;
    generateAndBindVAO(VAO3, VBO3, vertices3, sizeof(vertices3));

    std::string vertexShaderSource = readShaderSource("src/shaders/vertexShader.glsl");
    const char *vertexShaderCode = vertexShaderSource.c_str();

    std::string fragmentShaderSource = readShaderSource("src/shaders/fragmentShader.glsl");
    const char *fragmentShaderCode = fragmentShaderSource.c_str();

    std::string fragmentShaderYellowSource = readShaderSource("src/shaders/fragmentShaderYellow.glsl");
    const char *fragmentShaderYellowCode = fragmentShaderYellowSource.c_str();

    std::string fragmentShaderUniformSource = readShaderSource("src/shaders/fragmentShaderUniform.glsl");
    const char *fragmentShaderUniformCode = fragmentShaderUniformSource.c_str();

    unsigned int shaderProgram = createShaderProgram(vertexShaderCode, fragmentShaderCode);
    unsigned int shaderProgramYellow = createShaderProgram(vertexShaderCode, fragmentShaderYellowCode);
    unsigned int shaderProgramUniform = createShaderProgram(vertexShaderCode, fragmentShaderUniformCode);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        handleEscKey(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw second triangle
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // update uniform color on each render iteration
        glUseProgram(shaderProgramUniform);
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgramUniform, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAO3);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Callback to handle user resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void handleEscKey(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

std::string readShaderSource(const char *shaderFile) {
    std::ifstream shaderStream(shaderFile);
    std::stringstream shaderContent;
    shaderContent << shaderStream.rdbuf();
    return shaderContent.str();
}

void generateAndBindVAO(unsigned int &VAO, unsigned int &VBO, float *vertices, size_t size) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}

unsigned int compileShader(const char *shaderCode, GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return shader;
}

unsigned int createShaderProgram(const char *vertexShaderCode, const char *fragmentShaderCode) {
    unsigned int vertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}