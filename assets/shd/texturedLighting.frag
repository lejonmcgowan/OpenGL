#version 330

in vec3 worldCoord;
in vec3 surfaceNormal;
in vec2 textureCoords;

uniform sampler2D texIndex;

uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;


void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - worldCoord);
    float diffuseStrength = max(dot(lightDir,normalize(surfaceNormal)), 0.0f);

    vec3 diffuse = diffuseStrength * lightColor;

    vec4 textureColor = texture(texIndex,textureCoords);

    gl_FragColor = vec4((ambient + diffuse) * ambientColor * textureColor.xyz,1.0f);
}
