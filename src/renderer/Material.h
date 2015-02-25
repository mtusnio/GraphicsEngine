#ifndef H_MATERIAL
#define H_MATERIAL

#include <memory>
#include <string>
#include <map>

#include "Texture.h"

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

	std::shared_ptr<const Texture> AmbientTex;
	std::shared_ptr<const Texture> DiffuseTex;
	std::shared_ptr<const Texture> SpecularTex;
	std::shared_ptr<const Texture> NormalTex;
	std::map<std::string, std::string> Parameters;

};

#endif