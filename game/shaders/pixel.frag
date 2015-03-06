#version 420

in vec2 UV;
out vec4 color;

uniform sampler2D diffuseTexture;
uniform vec3 ambientIntensity;

void main()
{
    color = vec4(ambientIntensity, 1.0f) * texture(diffuseTexture, UV.xy);
}
