#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec2 textureCoords;
out vec3 surfaceNormal;
out vec3 worldCoord;

uniform mat4 model, view, projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	worldCoord = (model * vec4(position, 1.0f)).xyz;
	textureCoords = vec2(texCoords.x, 1.0f - texCoords.y);
	surfaceNormal = vec3(inverse(transpose(model)) * vec4(normal,1.0f));
}
