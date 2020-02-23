#include "./gtest/gtest.h"
#include "MemoryCache.hpp"
#include "PoorManMemoryCache.hpp"
#include "NullCache.hpp"
#include "FileCache.hpp"
#include "CacheApplier.hpp"
static std::vector<std::string> keys = { "key1","key2","key3","key4","key5","key6","key7","key8","key9","key10" };
static std::vector<std::string> other_keys = { "key11","key22","key33","key44","key55","key66","key77","key88","key99","key1010" };
static std::vector<std::string> values = { "value1","value2","value3","value4","value5","value6","value7","value8","value9","value10" };

TEST(Memory_cache_test, read_write) {
	MemoryCache mem_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		mem_cache.write(keys[i], values[i]);
	}
	std::string read_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		read_value = mem_cache.read(keys[i]);
		EXPECT_EQ(read_value, values[i]);
	}
}

TEST(Memory_cache_test, has) {
	MemoryCache mem_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		mem_cache.write(keys[i], values[i]);
	}
	bool has_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has_value = mem_cache.has(keys[i]);
		EXPECT_TRUE(has_value);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has_value = mem_cache.has(other_keys[i]);
		EXPECT_FALSE(has_value);
	}
}
TEST(Memory_cache_test, erase) {
	MemoryCache mem_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		mem_cache.write(keys[i], values[i]);
	}
	bool has_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		mem_cache.erase(keys[i]);
		has_value = mem_cache.has(keys[i]);
		EXPECT_FALSE(has_value);
	}
}
TEST(Poor_cache_test,read_write)
{
	PoorManMemoryCache poor_cache(10);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		poor_cache.write(keys[i], values[i]);
	}
	std::string read_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		read_value = poor_cache.read(keys[i]);
		EXPECT_EQ(read_value, values[i]);
	}
	bool has_value;
	for (int i = 0; i < (int)other_keys.size(); i++)
	{
		poor_cache.write(other_keys[i], values[i]);
		has_value = poor_cache.has(keys[i]);
		EXPECT_FALSE(has_value);
	}
}
TEST(Poor_cache_test, has)
{
	PoorManMemoryCache poor_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		poor_cache.write(keys[i], values[i]);
	}
	bool has_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has_value = poor_cache.has(keys[i]);
		EXPECT_TRUE(has_value);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has_value = poor_cache.has(other_keys[i]);
		EXPECT_FALSE(has_value);
	}
}

TEST(Poor_cache_test, erase) {
	PoorManMemoryCache poor_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		poor_cache.write(keys[i], values[i]);
	}
	bool has_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		poor_cache.erase(keys[i]);
		has_value = poor_cache.has(keys[i]);
		EXPECT_FALSE(has_value);
	}
}

TEST(Null_cache_test, read_write)
{
	NullCache null_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		null_cache.write(keys[i], values[i]);
	}
	std::string read_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		read_value = null_cache.read(keys[i]);
		EXPECT_EQ("", read_value);
	}
	
}
TEST(Null_cache_test, has)
{
	NullCache null_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		null_cache.write(keys[i], values[i]);
	}
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = null_cache.has(keys[i]);
		EXPECT_EQ(false, has);
	}

}
TEST(Null_cache_test, erase)
{
	NullCache null_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		null_cache.write(keys[i], values[i]);
	}
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		null_cache.erase(keys[i]);
		has = null_cache.has(keys[i]);
		EXPECT_EQ(false, has);
	}

}

TEST(File_cache_test, read_write) {
	FileCache file_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		file_cache.write(keys[i], values[i]);
	}
	std::string read_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		read_value = file_cache.read(keys[i]);
		EXPECT_EQ(read_value, values[i]);
	}
}

TEST(File_cache_test, has) {
	FileCache file_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		file_cache.write(keys[i], values[i]);
	}
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = file_cache.has(keys[i]);
		EXPECT_EQ(has, true);
	}
}
TEST(File_cache_test, erase) {
	FileCache file_cache;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		file_cache.write(keys[i], values[i]);
	}
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		file_cache.erase(keys[i]);
		has = file_cache.has(keys[i]);
		EXPECT_EQ(has, false);
	}
}
TEST(Poor_cache_test_applier, read_write_1_2)
{
	CacheApplier applier;
	applier.set_strategy(std::make_shared<PoorManMemoryCache>(10));
	applier.write_from_cache("1", "1");
	applier.write_from_cache("1", "2");
	EXPECT_EQ(applier.read_from_cache("1"), "2");
}

TEST(Cache_applier,work_with_memory_cache)
{
	CacheApplier applier;
	MemoryCache memory_cache;
	applier.set_strategy(std::make_shared<MemoryCache>(memory_cache));
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.write_from_cache(keys[i], values[i]);
	}
	std::string read_value;
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
		EXPECT_EQ(true, has);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
	}
}
TEST(Cache_applier, work_with_poor_man_memory_cache)
{
	CacheApplier applier;
	applier.set_strategy(std::make_shared<PoorManMemoryCache>(10));
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.write_from_cache(keys[i], values[i]);
	}
	std::string read_value;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
	}
	bool has_value;
	for (int i = 0; i < (int)other_keys.size(); i++)
	{
		applier.write_from_cache(other_keys[i], values[i]);
		has_value = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has_value);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.delete_from_cache(keys[i]);
		has_value = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has_value);
	}
}
TEST(Cache_applier, work_with_null_cache)
{
	CacheApplier applier;
	applier.set_strategy(std::make_shared<NullCache>());
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.write_from_cache(keys[i], values[i]);
	}
	std::string read_value;
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, "");
		EXPECT_EQ(false, has);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(false);
	}
}
TEST(Cache_applier, work_with_file_cache)
{
	CacheApplier applier;
	applier.set_strategy(std::make_shared<FileCache>());
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.write_from_cache(keys[i], values[i]);
	}
	std::string read_value;
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
		EXPECT_EQ(true, has);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
	}
}
TEST(Cache_applier, work_with_different_caches_memory_and_file)
{
	CacheApplier applier;
	std::shared_ptr<FileCache> file_cache_ptr(std::make_shared<FileCache>());
	std::shared_ptr<MemoryCache>  memory_cache_ptr(std::make_shared<MemoryCache>());
	applier.set_strategy(file_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.write_from_cache(keys[i], values[i]);
	}
	std::string read_value;
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
		EXPECT_EQ(true, has);
	}
	
	applier.set_strategy(memory_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
		applier.write_from_cache(keys[i], values[i]);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
		EXPECT_EQ(true, has);
	}
	
	applier.set_strategy(file_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_TRUE(has);
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
	}
	
	applier.set_strategy(memory_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_TRUE(has);
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
	}
}
TEST(Cache_applier, work_with_different_caches_poor_and_file_)
{
	CacheApplier applier;
	std::shared_ptr<FileCache> file_cache_ptr(std::make_shared<FileCache>());
	std::shared_ptr<PoorManMemoryCache> poor_cache_ptr(std::make_shared<PoorManMemoryCache>());
	applier.set_strategy(file_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.write_from_cache(keys[i], values[i]);
	}
	std::string read_value;
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
		EXPECT_EQ(true, has);
	}

	applier.set_strategy(poor_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
		applier.write_from_cache(keys[i], values[i]);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
		EXPECT_EQ(true, has);
	}

	applier.set_strategy(file_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_TRUE(has);
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
	}

	applier.set_strategy(poor_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_TRUE(has);
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
	}
}
TEST(Cache_applier, work_with_different_caches_poor_and_memory_)
{
	CacheApplier applier;
	std::shared_ptr<MemoryCache> memory_cache_ptr(std::make_shared<MemoryCache>());
	std::shared_ptr<PoorManMemoryCache> poor_cache_ptr(std::make_shared<PoorManMemoryCache>());
	applier.set_strategy(memory_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		applier.write_from_cache(keys[i], values[i]);
	}
	std::string read_value;
	bool has;
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
		EXPECT_EQ(true, has);
	}

	applier.set_strategy(poor_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
		applier.write_from_cache(keys[i], values[i]);
	}
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		read_value = applier.read_from_cache(keys[i]);
		EXPECT_EQ(read_value, values[i]);
		EXPECT_EQ(true, has);
	}

	applier.set_strategy(memory_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_TRUE(has);
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
	}

	applier.set_strategy(poor_cache_ptr);
	for (int i = 0; i < (int)keys.size(); i++)
	{
		has = applier.has_from_cache(keys[i]);
		EXPECT_TRUE(has);
		applier.delete_from_cache(keys[i]);
		has = applier.has_from_cache(keys[i]);
		EXPECT_FALSE(has);
	}
}