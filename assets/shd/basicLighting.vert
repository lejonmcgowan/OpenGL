#version 330

layout(location = 0) in vec3 location;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

void main()
{
	gl_Position = vec4(vec3(0.0), 1.0);
}
