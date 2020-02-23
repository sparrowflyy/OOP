#include "FileCache.hpp"
#include "fstream"
#include <iostream>
#include <vector>

void FileCache::write(const std::string& key, const std::string& value)
{
	bool isContainig = has(key);
	size_t hsh = hash_func(key);

	std::ofstream fouts(std::to_string(hsh), std::ios_base::app);
	fouts << key << " " << value << '\n';
	fouts.close();
	
}

std::string FileCache::read(const std::string& key)
{
	size_t hsh = hash_func(key);
	std::ifstream fins(std::to_string(hsh));
	std::string buf;
	fins >> buf;
	if (buf == key)
	{
		buf.clear();
		fins >> buf;
		fins.close();
		return buf;
	}
	fins.close();
	return "";

}
bool FileCache::check_other_key(std::ifstream& stream,const std::string& key)
{
	std::string buf;
	while(std::getline(stream,buf))
	{
		if (buf.find(key) == std::string::npos) return true;
	}
	return false;
}
void FileCache::write_without_key(std::ifstream& stream,const std::string& key)
{
	std::vector<std::string> data;
	std::string buf;
	while (std::getline(stream, buf))
	{
		if (buf.find(key) == std::string::npos)
		{
			data.push_back(buf);
		}
	}
	stream.close();
	size_t hsh = hash_func(key);
	std::ofstream fins(std::to_string(hsh), std::ios::out);
	for (auto it = data.begin();it!=data.end();++it)
	{
		fins << *it;
	}
}

void FileCache::erase(const std::string& key)
{
	size_t hsh = hash_func(key);
	std::string str_hsh = std::to_string(hsh);
	std::ifstream fins(str_hsh,std::ios::in);
	if (fins.is_open()) {
		bool hasOtherKeys = check_other_key(fins, key);
		if (hasOtherKeys == false) {
		
			fins.close();
			if (remove(str_hsh.c_str()) == -1) std::cerr << "Can't erase\n";
		}
		else
		{
			write_without_key(fins, key);
			
		}
	}	
	else
	{
		fins.close();
		std::cout << "Cache doesn't contain element " << key << '\n';
	}
}

bool FileCache::has(const std::string& key)
{
	size_t hsh = hash_func(key);
	std::ifstream fins(std::to_string(hsh));
	if (fins.is_open()) {
		fins.close();
		return true;
	}
	fins.close();
	return false;
}

