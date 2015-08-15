#version 330

in vec2 finalTextCoords;
out vec4 color;
uniform sampler2D textureColor1, textureColor2;

void main()
{
    color = mix(texture(textureColor1, finalTextCoords),texture(textureColor2, finalTextCoords),0.7);
    //color = finalTextCoords.xyxy;
}