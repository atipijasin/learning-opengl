#include <cstddef>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "initializeShaders.h"
#include "initializeWindow.h"

// Callback to handle user resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void handleEscKey(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    GLFWwindow *window = initializeWindow();
    if (window == NULL)
        return -1;

    unsigned int shaderProgram = initializeShaders(window);
    if (shaderProgram == -1)
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
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        handleEscKey(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
