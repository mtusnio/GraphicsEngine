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


in vec2 UV;
in vec3 fragmentPosition;
in vec3 fragmentNormal;
in vec4 ShadowCoord[MAX_SPOTLIGHTS];

out vec4 color;

uniform Spotlight Spotlights[MAX_SPOTLIGHTS];

uniform vec3 ambientIntensity;
uniform sampler2D ambientTexture;

uniform vec3 diffuseIntensity;
uniform sampler2D diffuseTexture;

uniform vec3 specularIntensity;
uniform sampler2D specularTexture;

uniform int SpotlightCount;
uniform sampler2DShadow Shadowmap[MAX_SPOTLIGHTS];

uniform mat4 M;

vec3 CalculateSpotlightDiffuse(Spotlight light, vec3 reflectionDirection, vec3 normal, float dist)
{     
    float diffuse = pow(max(0.0, dot(reflectionDirection, light.Direction)), light.Exponent) * max(0.0f, dot(normal, -reflectionDirection));
    vec3 clr = diffuse/(light.Constant + light.Linear * dist + light.Quadratic * pow(dist, 2.0)) * light.Color;
    return clamp(clr.xyz, 0.0, 1.0);
}

void main()
{
    vec3 diffuseColor = vec3(0.0);
    vec3 specularColor = vec3(0.0);
    vec4 pos = M * vec4(fragmentPosition, 1.0);
    vec4 normal = inverse(transpose(M)) * vec4(fragmentNormal, 0.0);
    for(int i = 0; i < SpotlightCount; i++)
    {
        vec3 diff = fragmentPosition - Spotlights[i].Position;
        vec3 direction = normalize(diff);
        float dist = length(diff);
        float ang = degrees(acos(dot(direction, Spotlights[i].Direction)));
        if(ang > Spotlights[i].Cone/2.0 || dist > Spotlights[i].MaxDistance)
            continue;
        
        float shadow = textureProj(Shadowmap[i], ShadowCoord[i], 0.005f);
        diffuseColor += CalculateSpotlightDiffuse(Spotlights[i], direction, normal.xyz, dist)  * shadow;
    }
    
    vec4 diffuseTex = texture(diffuseTexture, UV.xy);
    vec4 ambientTex = texture(ambientTexture, UV.xy);
    color = vec4(ambientIntensity, 1.0) * ambientTex + vec4(diffuseIntensity, 1.0) * diffuseTex * vec4(diffuseColor, 1.0);
}
