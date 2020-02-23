#pragma once
#include "BaseCache.hpp"

class NullCache :public BaseCache {
public:
	bool has(const std::string &key);
	std::string read(const std::string &key);
	void write(const std::string &key, const std::string &value);
	void erase(const std::string &key);
};

