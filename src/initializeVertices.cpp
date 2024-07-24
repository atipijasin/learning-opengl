#include "initializeVertices.h"
#include <glad/glad.h>

void initializeVertices() {
    // simple vertices represented as Normalized Device Coordinates
    // (NDC)
    float vertices[] = {
        -1.0f, -0.5f, 0.0f, 0.0f, -0.5f, 0.0f, -0.5f, 0.25f, 0.0f,
        1.0f,  -0.5f, 0.0f, 0.0f, -0.5f, 0.0f, 0.5f,  0.25f, 0.0f,
    };

    unsigned int vertexIndices[] = {0, 1, 3, 1, 2, 3};

    // bind VAO
    unsigned int VAO; // Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // copy vertices array in a vertex buffer for OpenGL to use
    unsigned int VBO; // Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
}
