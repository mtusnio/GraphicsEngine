#ifndef H_MATERIAL
#define H_MATERIAL

#include <memory>
#include <string>
#include <map>

struct Texture
{

};

struct Material
{
	float Ambient[3];
	float Diffuse[3];
	float Specular[3];
	float Transmittance[3];
	float Emission[3];
	float Shininess;
	float IndexOfRefraction;
	float Opaque; 

	int IlluminationModel;

	std::shared_ptr<Texture> AmbientTex;
	std::shared_ptr<Texture> DiffuseTex;
	std::shared_ptr<Texture> SpecularTex;
	std::shared_ptr<Texture> NormalTex;
	std::map<std::string, std::string> Parameters;

};

#endif