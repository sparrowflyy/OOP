#include "MemoryCache.hpp"

MemoryCache::~MemoryCache()
{
	data_map.clear();
}

inline void MemoryCache::write(const std::string& key, const std::string& value)
{
	data_map[key] = value;
}

inline std::string MemoryCache::read(const std::string& key)
{
	auto it = data_map.find(key);
	if (it != data_map.end()) return it->second;
	return {};				//hype
}

inline bool MemoryCache::has(const std::string& key)
{
	auto it = data_map.find(key);
	return it != data_map.end();
}

inline void MemoryCache::erase(const std::string& key)
{
	data_map.erase(key);
}