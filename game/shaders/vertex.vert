#version 420

#define MAX_SPOTLIGHTS 8


layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec4 ShadowCoord[MAX_SPOTLIGHTS];

uniform mat4 MVP;
uniform int SpotlightCount;
uniform mat4 SpotlightMVP[MAX_SPOTLIGHTS];


void main()
{
    UV = texCoords;
    fragmentPosition = vertexPosition;
    fragmentNormal = vertexNormal;

    for(int i = 0; i < SpotlightCount; i++)
    {
        ShadowCoord[i] = SpotlightMVP[i] * vec4(vertexPosition, 1.0f);
    }
    
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
}