#version 420

in vec2 UV;
in vec3 LightColor;
out vec4 color;

uniform vec3 ambientIntensity;

uniform vec3 diffuseIntensity;
uniform sampler2D diffuseTexture;


void main()
{
    vec4 tex = texture(diffuseTexture, UV.xy);
    color = vec4(ambientIntensity, 1.0) * tex + vec4(diffuseIntensity, 1.0) * tex * vec4(LightColor, 1.0f);
}
