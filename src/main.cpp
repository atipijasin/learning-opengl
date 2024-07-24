#include <cstddef>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "initializeShaders.h"
#include "initializeVertices.h"
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

    initializeVertices();
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        handleEscKey(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        // currently drawing a rectngle using two triangles, that's why 6
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
