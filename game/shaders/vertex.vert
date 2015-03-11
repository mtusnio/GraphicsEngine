#version 420

struct Spotlight
{
    vec3 Direction;
    vec3 Position;
    vec3 Color;
    float Exponent;
    float Linear;
    float Constant;
    float Quadratic;
};

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 texCoords;

out vec2 UV;
out vec3 LightColor;

uniform mat4 MVP;
uniform int SpotlightCount;
uniform Spotlight Spotlights[8];

vec3 CalculateSpotlight(Spotlight light, vec3 position)
{
    vec3 diff = light.Position - position;
    vec3 direction = normalize(diff.xyz);
    float dist = length(diff);
    
    vec3 clr = (pow(max(0.0, dot(direction, light.Direction)), light.Exponent)/(light.Constant + light.Linear * dist + pow(light.Quadratic, 2.0) * dist)) * LightColor;
    return clr;
}

void main()
{
    UV = texCoords;
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
    
    LightColor = vec3(0.0f);
    for(int i = 0; i < SpotlightCount; i++)
    {
        LightColor = LightColor + CalculateSpotlight(Spotlights[i], gl_Position.xyz);
    }
}