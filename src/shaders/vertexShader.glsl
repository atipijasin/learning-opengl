#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 darkRedVertexColor; // specify this output to be used by the fragment shader

void main()
{
    // gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    // gl_Position = vec4(aPos.xyz, 1.0); // swizzling
    gl_Position = vec4(aPos, 1.0); // swizzling

    darkRedVertexColor = vec4(0.5, 0.0, 0.0, 1.0); // define color, which can be used in other fragment shaders 
}
