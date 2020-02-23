#pragma once
#include "BaseCache.hpp"
class FileCache:public BaseCache {
public:
	FileCache() = default;
	bool has(const std::string &key) override;
	std::string read(const std::string &key) override;
    void write(const std::string &key, const std::string &value) override;
	void erase(const std::string &key) override;
private:
	std::hash<std::string> hash_func;
	bool check_other_key(std::ifstream& stream, const std::string& key);
	void write_without_key(std::ifstream& stream,const std::string& key);
};


