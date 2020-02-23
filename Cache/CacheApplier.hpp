#pragma once
#include "BaseCache.hpp"
class CacheApplier {
public:
	void set_strategy(std::shared_ptr<BaseCache> strategy);
	std::string read_from_cache(const std::string &key);
	void write_from_cache(const std::string &key, const std::string &value);
	void delete_from_cache(const std::string &key); 
	bool has_from_cache(const std::string &key);
private:
	std::shared_ptr<BaseCache> cache;
};