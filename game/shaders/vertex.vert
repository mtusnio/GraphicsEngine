#version 420

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 texCoords;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vertexPosition, 1.0f);
}