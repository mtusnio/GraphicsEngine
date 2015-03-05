#version 420

in vec2 UV;
out vec4 color;

uniform sampler2D diffuseTexture;

void main()
{
    color = texture(diffuseTexture, UV.xy);
}
