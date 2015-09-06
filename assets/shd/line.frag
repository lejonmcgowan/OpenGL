#version 330 core

in vec3 finalColor;
void main()
{
	gl_FragColor = vec4(finalColor,1.0f);
}
