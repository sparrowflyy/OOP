#pragma once
#include "BaseCache.hpp"
#include <list>
class PoorManMemoryCache :public BaseCache {
public:
	PoorManMemoryCache(int n=64);
	~PoorManMemoryCache();
	bool has(const std::string &key);
	std::string read(const std::string &key);
	void write(const std::string &key, const std::string &value);
	void erase(const std::string &key);
private:
	const int N;
	std::list<std::pair<std::string,std::string>> data;
	std::list<std::pair<std::string, std::string>>::iterator find(const std::string& key);
};





