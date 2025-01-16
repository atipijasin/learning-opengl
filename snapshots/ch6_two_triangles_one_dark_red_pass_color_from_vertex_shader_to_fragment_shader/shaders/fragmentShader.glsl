#version 330 core
out vec4 FragColor;

in vec4 darkRedVertexColor; // input from vertx shader

void main()
{
    FragColor = darkRedVertexColor;
}
