#version 330

uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
const float specularStrength = 0.5f;

uniform sampler2D textureHandle;

in vec3 surfaceNormal;
in vec3 worldCoord;

void main()
{
	//calculate ambient contribution
	float ambeintStrength = 0.1f;
	vec3 ambient = ambeintStrength * lightColor;

	vec3 lightDir = normalize(lightPos - worldCoord);
	float difffuseStrength = max(dot(lightDir,normalize(surfaceNormal)), 0.0f);
    vec3 diffuse = difffuseStrength * lightColor;

    vec3 viewDir = normalize(viewPos - worldCoord);
    vec3 reflectDir = reflect(-lightDir,surfaceNormal);
    float specExponent = pow(max(dot(viewDir,reflectDir),0.0f),64);

	vec3 specular = specularStrength * specExponent * lightColor;
	vec3 result = (ambient + diffuse + specular) * ambientColor;
	gl_FragColor = vec4(result, 1.0f);
}
