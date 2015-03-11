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
    float Cone;
};

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 LightColor;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 M;
uniform int SpotlightCount;
uniform Spotlight Spotlights[8];

vec3 CalculateSpotlight(Spotlight light, vec3 position)
{
    vec3 diff = position - light.Position;
    float dist = length(diff);
    vec3 direction = normalize(diff);
    
    float ang = degrees(acos(dot(diff, light.Direction)));
    
    if(ang > light.Cone)
        return vec3(0.0f);
        
    vec3 clr = (pow(max(0.0, dot(direction, light.Direction)), light.Exponent)/(light.Constant + light.Linear * dist + light.Quadratic * pow(dist, 2.0))) * light.Color;
    return clamp(clr.xyz, 0.0, 1.0);
}

void main()
{
    UV = texCoords;
   
    LightColor = vec3(0.0f);
    vec4 pos = M * vec4(vertexPosition, 1.0);
    for(int i = 0; i < SpotlightCount; i++)
    {
        LightColor = LightColor + CalculateSpotlight(Spotlights[i], pos.xyz);
    }
    
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
}