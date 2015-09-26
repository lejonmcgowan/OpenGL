#version 330

uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform sampler2D textureHandle;

in vec2 textureCoords;

void main()
{
	float ambeintStrength = 0.1f;
	vec3 ambient = ambeintStrength * lightColor;
    //vec4 textureColor = texture(textureHandle,textureCoords);
	vec3 result = ambient * ambientColor;

	gl_FragColor = vec4(result, 1.0f);
}
