#version 420

#define MAX_SPOTLIGHTS 8

in vec2 UV;
in vec3 SpotlightColor[MAX_SPOTLIGHTS];

out vec4 color;


uniform int SpotlightCount;

uniform vec3 ambientIntensity;

uniform vec3 diffuseIntensity;
uniform sampler2D diffuseTexture;


void main()
{
    vec3 clr = vec3(0.0);
    for(int i = 0; i < SpotlightCount; i++)
    {
        clr += SpotlightColor[i];
    }
    
    vec4 tex = texture(diffuseTexture, UV.xy);
    color = vec4(ambientIntensity, 1.0) * tex + vec4(diffuseIntensity, 1.0) * tex * vec4(clr, 1.0);
}
