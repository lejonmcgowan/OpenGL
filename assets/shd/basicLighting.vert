#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec2 textureCoords;

uniform mat4 model, view, projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	textureCoords = texCoords;
}
