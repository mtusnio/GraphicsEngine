#version 420

#define MAX_SPOTLIGHTS 8

struct Spotlight
{
    vec3 Direction;
    vec3 Position;
    vec3 Color;
    float Exponent;
    float Linear;
    float Constant;
    float Quadratic;
    float Cone;
    float MaxDistance;
};

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 SpotlightColor[MAX_SPOTLIGHTS];

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 M;
uniform int SpotlightCount;
uniform Spotlight Spotlights[MAX_SPOTLIGHTS];

vec3 CalculateSpotlight(Spotlight light, vec3 position)
{
    vec3 diff = position - light.Position;
    float dist = length(diff);
    vec3 direction = normalize(diff);
    
    float ang = degrees(acos(dot(direction, light.Direction)));
    
    
    if(ang > light.Cone/2.0 || dist > light.MaxDistance)
        return vec3(0.0f);
        
    vec3 clr = (pow(max(0.0, dot(direction, light.Direction)), light.Exponent)/(light.Constant + light.Linear * dist + light.Quadratic * pow(dist, 2.0))) * light.Color;
    return clamp(clr.xyz, 0.0, 1.0);
}

void main()
{
    UV = texCoords;
   
    vec4 pos = M * vec4(vertexPosition, 1.0);
    for(int i = 0; i < SpotlightCount; i++)
    {
        SpotlightColor[i] = CalculateSpotlight(Spotlights[i], pos.xyz);
    }
    
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
}