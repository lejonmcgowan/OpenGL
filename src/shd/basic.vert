#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureInput;

out vec2 finalTextCoords;

void main()
{
    gl_Position = vec4(position, 1.0f);
    finalTextCoords = textureInput;
}