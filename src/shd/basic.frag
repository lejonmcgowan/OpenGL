#version 330

in vec2 finalTextCoords;
out vec4 color;
uniform sampler2D textureColor;

void main()
{
    color = texture(textureColor, finalTextCoords);
    //color = finalTextCoords.xyxy;
}