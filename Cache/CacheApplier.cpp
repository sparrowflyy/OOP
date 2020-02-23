#include "CacheApplier.hpp"

void CacheApplier::set_strategy(std::shared_ptr<BaseCache> strategy)
{
	cache = strategy;
}

void CacheApplier::delete_from_cache(const std::string& key)
{
	cache->erase(key);
}

void CacheApplier::write_from_cache(const std::string& key, const std::string& value)
{
	cache->write(key, value);
}

std::string CacheApplier::read_from_cache(const std::string& key)
{
	return cache->read(key);
}

bool CacheApplier::has_from_cache(const std::string& key)
{
	return cache->has(key);
}



