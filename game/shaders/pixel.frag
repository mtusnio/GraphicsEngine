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

uniform vec3 cameraPosition;

uniform Spotlight Spotlights[MAX_SPOTLIGHTS];

uniform vec3 ambientIntensity;
uniform sampler2D ambientTexture;

uniform vec3 diffuseIntensity;
uniform sampler2D diffuseTexture;

uniform vec3 specularIntensity;
uniform sampler2D specularTexture;
uniform float shininess;

uniform int SpotlightCount;
uniform sampler2DShadow Shadowmap[MAX_SPOTLIGHTS];

uniform mat4 M;

vec3 CalculateSpotlightDiffuse(Spotlight light, vec3 surfaceToLight, vec3 normal, float dist)
{     
    float diffuse = pow(max(0.0, dot(-surfaceToLight, light.Direction)), light.Exponent) * max(0.0f, dot(normal, surfaceToLight));
    vec3 clr = diffuse/(light.Constant + light.Linear * dist + light.Quadratic * pow(dist, 2.0)) * light.Color;
    return clamp(clr.xyz, 0.0, 1.0);
}

vec3 CalculateSpotlightSpecular(Spotlight light, vec3 surfaceToLight, vec3 surfaceToCamera, vec3 normal)
{
    vec3 clr = vec3(0.0);
    
    // Make sure it's not facing away from light
    return clamp(clr.xyz, 0.0, 1.0) * max(0.0, dot(normal, surfaceToLight));
}


void main()
{
    vec3 diffuseColor = vec3(0.0);
    vec3 specularColor = vec3(0.0);
    vec4 pos = M * vec4(fragmentPosition, 1.0);
    vec4 normal = inverse(transpose(M)) * vec4(fragmentNormal, 0.0);
    vec3 surfaceToCamera = normalize(cameraPosition - pos.xyz);
    for(int i = 0; i < SpotlightCount; i++)
    {
        vec3 diff = Spotlights[i].Position - pos.xyz;
        vec3 direction = normalize(diff);
        float dist = length(diff);
        float ang = degrees(acos(dot(-direction, Spotlights[i].Direction)));
        if(ang > Spotlights[i].Cone/2.0 || dist > Spotlights[i].MaxDistance)
            continue;
        
        float shadow = textureProj(Shadowmap[i], ShadowCoord[i], 0.005f);
        diffuseColor += CalculateSpotlightDiffuse(Spotlights[i], direction, normal.xyz, dist)  * shadow;
        specularColor += CalculateSpotlightSpecular(Spotlights[i], direction, surfaceToCamera, normal.xyz) * shadow;
    }
    
    vec4 diffuseTex = texture(diffuseTexture, UV.xy);
    vec4 ambientTex = texture(ambientTexture, UV.xy);
    vec4 specularTex = texture(specularTexture, UV.xy);
    
    color = vec4(ambientIntensity, 1.0) * ambientTex + vec4(diffuseIntensity, 1.0) * diffuseTex * vec4(diffuseColor, 1.0) /*+ vec4(specularIntensity, 1.0) * specularTex * vec4(specularColor, 1.0)*/;
}
