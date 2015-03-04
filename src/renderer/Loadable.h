#ifndef H_LOADABLE
#define H_LOADABLE

#include <string>

struct Loadable
{
	virtual ~Loadable() { };

	// Returns empty string on success, error on failure
	virtual std::string Load(const std::string & path) = 0;
};

#endif