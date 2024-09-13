#pragma Vertex
#version 450

layout (location = 0) in vec2 Pos;
layout (location = 1) in vec2 TexCoord;

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

out vec2 UV;

void main()
{
    gl_Position = Projection * View * Transform * vec4(Pos.x, Pos.y, 0.0, 1.0);
    UV = TexCoord;
}

#pragma Fragment
#version 450

in vec2 UV;
out vec4 Color;

uniform sampler2D TEX;

void main()
{
    Color = texture(TEX, UV);
}
