#include "PoorManMemoryCache.hpp"

PoorManMemoryCache::PoorManMemoryCache(int n) : N(n) {}


PoorManMemoryCache::~PoorManMemoryCache()
{
	data.clear();
}

inline std::list<std::pair<std::string, std::string>>::iterator PoorManMemoryCache::find(const std::string& key)
{
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		if (it->first == key) return it;
	}
	return data.end();
}

inline bool PoorManMemoryCache::has(const std::string& key)
{
	return find(key) != data.end();
}

inline void PoorManMemoryCache::write(const std::string& key, const std::string& value)
{
	bool isContaning = has(key);
	if (isContaning)
	{
		auto it = find(key);
		data.erase(it);
		data.push_back({ key,value });
		return;
	}
	
	if ((int)data.size() < N)
	{																									 
		data.push_back({ key,value });							 																	
		return;
	}
	if ((int)data.size()==N)
	{
		data.erase(data.begin());
		data.push_back({ key,value });
	}
}
inline std::string PoorManMemoryCache::read(const std::string& key)
{
	auto it = find(key);
	if (it != data.end()) return it->second;
	return "";
}
inline void PoorManMemoryCache::erase(const std::string& key)
{
	auto it = find(key);
	if (it != data.end()) data.erase(it);
}