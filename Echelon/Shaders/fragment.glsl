#version 450

in vec2 UV;
out vec4 Color;

uniform sampler2D TEX;

void main()
{
    Color = texture(TEX, UV);
}