#ifndef H_MATERIALMANAGER
#define H_MATERIALMANAGER

#include "AssetManager.h"
#include "../renderer/Material.h"

template<class T, class Derived>
class LoadablesManager : public AssetManager<Derived>
{
public:
	LoadablesManager(IGame & game) : AssetManager<Derived>(game) { };
	virtual ~LoadablesManager() { };

private:
	virtual Derived * PerformCache(const std::string & path) const;
};

template<class T, class Derived>
Derived * LoadablesManager<T, Derived>::PerformCache(const std::string & path) const
{
	T * asset = new T();

	std::string error = "";
	if ((error = asset->Load(path)) != "")
	{
		delete asset;
		throw AssetError(error);
	}
	return asset;
}

#endif