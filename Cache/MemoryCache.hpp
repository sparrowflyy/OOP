#pragma once
#include "BaseCache.hpp"
#include <unordered_map>
class MemoryCache : public BaseCache
{
public:
	MemoryCache() = default;
	~MemoryCache();
	bool has(const std::string &key);
	std::string read(const std::string &key);
	void write(const std::string &key, const std::string &value);
	void erase(const std::string &key);
private:
	std::unordered_map<std::string, std::string> data_map;
};




