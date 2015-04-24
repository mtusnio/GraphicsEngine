#ifndef H_MATERIALMANAGER
#define H_MATERIALMANAGER

#include "AssetManager.h"
#include "../renderer/Material.h"

#include "../renderer/Loadable.h"

template<class T, class Derived>
class LoadablesManager : public AssetManager<Derived>
{
public:
	LoadablesManager(IGame & game) : AssetManager<Derived>(game) { };
	virtual ~LoadablesManager() { };

private:
	virtual Derived * PerformCache(const std::string & path);
};

template<class T, class Derived>
Derived * LoadablesManager<T, Derived>::PerformCache(const std::string & path)
{
	T * asset = new T();

	std::string error = "";
	if ((error = asset->Load(path)) != "")
	{
		delete asset;
		m_LastError = error;
		return nullptr;
	}
	return asset;
}

#endif