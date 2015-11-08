const int LIMIT = 10;

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform int numDirLights;
uniform int numPointLights;
uniform int numSpotLights;

uniform DirLight  dirLight[LIMIT];
uniform SpotLight spotLight[LIMIT];
uniform DirLight  dirLight[LIMIT];

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