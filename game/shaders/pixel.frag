#version 420

in vec2 UV;
in vec3 LightColor;
out vec4 color;

uniform sampler2D diffuseTexture;
uniform vec3 ambientIntensity;

void main()
{
    vec4 tex = texture(diffuseTexture, UV.xy);
    color = vec4(ambientIntensity, 1.0f) * tex + vec4(LightColor, 1.0f) * tex;
}
