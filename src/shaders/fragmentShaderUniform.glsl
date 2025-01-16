#version 330 core
out vec4 FragColor;

uniform vec4 ourColor; // input from vertx shader

void main()
{
    FragColor = ourColor;
}
