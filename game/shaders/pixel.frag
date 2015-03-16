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

uniform vec3 diffuseIntensity;
uniform sampler2D diffuseTexture;

uniform vec3 specularIntensity;
uniform sampler2D specularTexture;

uniform int SpotlightCount;
uniform sampler2DShadow Shadowmap[MAX_SPOTLIGHTS];

uniform mat4 M;

vec3 CalculateSpotlight(Spotlight light, vec3 position, vec3 normal)
{
    vec3 diff = position - light.Position;
    float dist = length(diff);
    vec3 direction = normalize(diff);
    
    float ang = degrees(acos(dot(direction, light.Direction)));
    
    
    if(ang > light.Cone/2.0 || dist > light.MaxDistance)
        return vec3(0.0f);
        
    vec3 clr = (pow(max(0.0, dot(direction, light.Direction)), light.Exponent)/(light.Constant + light.Linear * dist + light.Quadratic * pow(dist, 2.0))) * light.Color * max(0.0f, dot(normal, -direction));
    return clamp(clr.xyz, 0.0, 1.0);
}

void main()
{
    vec3 clr = vec3(0.0);
    vec4 pos = M * vec4(fragmentPosition, 1.0);
    vec4 normal = inverse(transpose(M)) * vec4(fragmentNormal, 0.0);
    for(int i = 0; i < SpotlightCount; i++)
    {
        float shadow = textureProj(Shadowmap[i], ShadowCoord[i], 0.005f);
        clr += CalculateSpotlight(Spotlights[i], pos.xyz, normal.xyz)  * shadow;
    }
    
    vec4 tex = texture(diffuseTexture, UV.xy);
    color = vec4(ambientIntensity, 1.0) * tex + vec4(diffuseIntensity, 1.0) * tex * vec4(clr, 1.0);
}
