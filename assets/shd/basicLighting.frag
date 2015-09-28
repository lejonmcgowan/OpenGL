#version 330

uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

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

	vec3 result = (ambient + diffuse) * ambientColor;
	gl_FragColor = vec4(result, 1.0f);
}
