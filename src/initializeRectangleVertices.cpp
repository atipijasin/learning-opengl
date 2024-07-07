#include "initializeRectangleVertices.h"
#include <glad/glad.h>

void initializeRectangleVertices() {
    // simple rectangle vertices represented as Normalized Device Coordinates
    // (NDC)
    float vertices[] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };

    // The coordinates are actually used to draw two triangles to make a
    // rectangle
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
    // copy index array in an element buffer for OpenGL to use
    unsigned int EBO; // Element Buffer Object
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
}
