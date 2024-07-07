#include <cstddef>
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

// Simple vertex shader to directly forward incoming Coordinates
// TODO move this to a file
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Simple fragment shader with orange-ish color
// TODO move this to a file
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

// Callback to handle user resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void handleEscKey(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow *initialize() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window =
        glfwCreateWindow(640, 480, "Learning OpenGL :)", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }

    glViewport(0, 0, 800, 600);

    // Register callback for user resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

int main() {
    GLFWwindow *window = initialize();
    if (window == NULL)
        return -1;

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int shadeCompilationSuccessful;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shadeCompilationSuccessful);

    if (!shadeCompilationSuccessful) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,
                  &shadeCompilationSuccessful);
    if (!shadeCompilationSuccessful) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Shaders are no loaded and no longer necessary at this point
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int programCompilationSuccessful;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS,
                   &programCompilationSuccessful);
    if (!programCompilationSuccessful) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                  << infoLog << std::endl;
    }

    // simple vertices represented as Normalized Device Coordinates
    // (NDC)
    float vertices[] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
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
    // copy index array in an element buffer for OpenGL to use
    unsigned int EBO; // Element Buffer Object
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        handleEscKey(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
