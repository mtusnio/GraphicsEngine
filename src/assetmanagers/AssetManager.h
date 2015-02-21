#ifndef H_ASSETMANAGER
#define H_ASSETMANAGER

#include <string>
#include <unordered_map>
#include <memory>

class IGame;

template<typename T>
class AssetManager
{
public:
	AssetManager(IGame & game);
	virtual ~AssetManager();

	// Caches the asset or returns it if it's already in cache.
	// nullptr if file not found
	std::shared_ptr<const T> Cache(const std::string & path);

	// Acts like the cache function, but doesn't cache, only checks
	// for existings files
	std::shared_ptr<const T> GetAsset(const std::string & path);

protected:
	IGame & m_Game;

private:
	// Derived classes should load the data into an object here and return it
	// for it to be added to the map by the AssetManager
	virtual T * PerformCache(const std::string & path) = 0;


	// Maps our paths to loaded assets.
	// Using shared_ptr/weak_ptr architecture to possibly add dynamic
	// removal of objects once they run out of scope
	std::unordered_map<std::string, std::weak_ptr<T>> m_Assets;
};

template<typename T>
AssetManager<T>::AssetManager(IGame & game) :
m_Game(game)
{

}

template<typename T>
AssetManager<T>::~AssetManager()
{
	
}

template<typename T>
std::shared_ptr<const T> AssetManager<T>::Cache(const std::string & path)
{
	std::shared_ptr<const T> ptr = GetAsset(path);

	if (ptr.get() != nullptr)
		return ptr;

	T * asset = PerformCache(path);

	if (!asset)
		return nullptr;

	ptr = std::shared_ptr<const T>(asset);
	m_Assets[path] = ptr;
	return ptr;
}

template<typename T>
std::shared_ptr<const T> AssetManager<T>::GetAsset(const std::string & path)
{
	auto it = m_Assets.find(path);
	if (it != m_Assets.end())
	{
		if (it->second.expired())
			return nullptr;

		return it->second.lock();
	}
		

	return nullptr;
}




#endif