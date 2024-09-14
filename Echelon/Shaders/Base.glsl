#pragma Vertex
#version 450 core

layout (location = 0) in vec2 Pos;
layout (location = 1) in vec2 TexCoord;

out vec2 WorldPos;
out vec2 UV;

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * View * Transform * vec4(Pos.x, Pos.y, 0.0, 1.0);
    WorldPos = (Transform * vec4(Pos.x, Pos.y, 0.0, 1.0)).xy;
    UV = TexCoord;
}

#pragma Fragment
#version 450 core

#define MAX_LIGHTS 10
struct Light
{
    vec2 Pos;
    vec3 Color;
    float Intensity;
    float Radius;
};

in vec2 WorldPos;
in vec2 UV;

out vec4 Color;

uniform Light Lights[MAX_LIGHTS];
uniform int LightCount;

uniform mat4 View;
uniform mat4 Projection;
uniform sampler2D TEX;

vec2 WorldToTangent(vec2 pos)
{
    vec4 viewPos = (View * vec4(pos, 0.0, 1.0)).xyzw;
    vec4 clipPos = (Projection * viewPos).xyzw;

    return clipPos.xy / clipPos.w * 0.5 + 0.5;
}

void main()
{
    // Basic Ambient Light - Constant lighting
    float ambientStrength = 0.2;
    vec3 ambientColor = ambientStrength * vec3(1.0, 1.0, 1.0);

    vec3 lighting = ambientColor;

    for (int i = 0; i < LightCount; i++)
    {
        float dist = length(Lights[i].Pos - WorldPos);
        float attenuation = smoothstep(Lights[i].Radius, 0.0, dist * 0.01);

        float intensity = mix(0.0, Lights[i].Intensity, attenuation);
        vec3 lightColor = Lights[i].Color * intensity;
        lighting += lightColor;
    }

    vec4 texColor = texture(TEX, UV);
    Color = vec4(lighting * texColor.rgb, texColor.a);
}

