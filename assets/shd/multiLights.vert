layout(location = 0) vec3 position;
layout(location = 1) vec3 normals;
layout(location = 2) vec2 texureCoordinates;

uniform mat4 model,view,projection;

out vec3 viewPos;
out vec2 texCoords;
out vec3 normal;
void main()
{
    texCoords = texureCoordinates;
    gl_Position = projection * view * model * vec4(position,1.0f);
    viewPos = (projection * view * vec4(position,1.0f)).xyz;
    normal = mat3(transpose(inverse(model))) * normals;
}