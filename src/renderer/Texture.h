#ifndef H_TEXTURE
#define H_TEXTURE

#include <string>

struct Texture
{
	virtual void Load(const std::string & path) = 0;
};

#endif