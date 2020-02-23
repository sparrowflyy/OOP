#include "./gtest/gtest.h"
#include "./gtest/gtest-memleak.h"
#include <cstdio>
#include "..//trie/trie.hpp"
#include <vector>
#include <map>
#include <algorithm>

static std::vector<std::string> keys = {
"Alex1","Peter1","Jack1","Wilson1","Mike1","Robert1","Norman1","Alan1","Pudge1","Ron1","Jerry1",
"Alex2","Peter2","Jack2","Wilson2","Mike2","Robert2","Norman2","Alan2","Pudge2","Ron2","Jerry2",
"Alex3","Peter3","Jack3","Wilson3","Mike3","Robert3","Norman3","Alan3","Pudge3","Ron3","Jerry3",
"Alex4","Peter4","Jack4","Wilson4","Mike4","Robert4","Norman4","Alan4","Pudge4","Ron4","Jerry4",
"Alex5","Peter5","Jack5","Wilson5","Mike5","Robert5","Norman5","Alan5","Pudge5","Ron5","Jerry5",
"Alex6","Peter6","Jack6","Wilson6","Mike6","Robert6","Norman6","Alan6","Pudge6","Ron6","Jerry6",
"Alex7","Peter7","Jack7","Wilson7","Mike7","Robert7","Norman7","Alan7","Pudge7","Ron7","Jerry7",
"Alex8","Peter8","Jack8","Wilson8","Mike8","Robert8","Norman8","Alan8","Pudge8","Ron8","Jerry8",
"Alex9","Peter9","Jack9","Wilson9","Mike9","Robert9","Norman9","Alan9","Pudge9","Ron9","Jerry9",
"Alex10","Peter10","Jack10","Wilson10","Mike10","Robert10","Norman10","Alan10","Pudge10","Ron10","Jerry10" };

static void fill_trie(Trie<int>& trie)
{
	for (size_t i =0;i<keys.size();i++)
	{
		trie.insert(keys[i], i);
	}
}

static void fill_map(std::map<const std::string,int>& map)
{
	for (size_t i = 0; i < keys.size(); i++)
	{
		map.insert({ keys[i], i });										 
	}
}

TEST(trie_,iter)
{
	Trie<int> trie;
	trie.insert("Asd", 1);
	trie.insert("D", 2);
	/*auto it = trie.begin();
	++it;*/
	trie.clear();
	
}
TEST(trie_size,empty)
{
	Trie<int> trie;
	EXPECT_TRUE(trie.empty());
}
TEST(trie_size,size)
{
	Trie<int> trie;
	fill_trie(trie);
	EXPECT_TRUE(trie.size() == keys.size());
}

TEST(trie_structure, swap) {
	Trie<int> trie;
	fill_trie(trie);
	Trie<int> another_trie;
	another_trie.swap(trie);
	EXPECT_TRUE(trie.empty());
	EXPECT_TRUE(another_trie.size() == keys.size());
	size_t count = 0;
	std::vector <std::string> checked_keys(keys);
	for (auto t = another_trie.begin(); t != another_trie.end(); ++t)
	{
		count++;
		auto found = std::find(checked_keys.begin(), checked_keys.end(), (*t).first);
		EXPECT_TRUE((*t).first == *found);
		checked_keys.erase(found);
	}
	EXPECT_TRUE(checked_keys.empty());
	EXPECT_TRUE(count == keys.size());
	trie.insert("a", 1);
	EXPECT_TRUE(another_trie.find("a") == another_trie.end());
}
TEST(trie_structure, copy_cons)
{
	Trie<int> trie;
	fill_trie(trie);
	Trie<int> another_trie(trie);
	EXPECT_TRUE(another_trie.size()==trie.size());
	size_t count = 0;
	std::vector <std::string> checked_keys(keys);
	for (auto t = another_trie.begin(); t != another_trie.end(); ++t)
	{
		count++;
		auto found = std::find(checked_keys.begin(), checked_keys.end(), (*t).first);
		EXPECT_TRUE((*t).first == *found);
		checked_keys.erase(found);
	}
	trie.insert("blablabla",6);
	EXPECT_TRUE(another_trie.find("blablabla") == another_trie.end());
}
TEST(trie_iterator,not_equal)
{
	Trie<int> trie;
	trie.insert("a", 1);
	trie.insert("b", 2);
	auto it1 = trie.find("a");
	auto it2 = trie.find("b");
	EXPECT_TRUE(it1 != it2);
}
TEST(const_trie_iterator, not_equal)
{
	Trie<int> trie;
	trie.insert("a", 1);
	trie.insert("b", 2);
	auto it1 = trie.cfind("a");
	auto it2 = trie.cfind("b");
	EXPECT_TRUE(it1 != it2);
}
TEST(trie_iterator,equating)
{
	Trie<int> trie;
	trie.insert("a", 1);
	trie.insert("b", 2);
	auto it1 = trie.find("a");
	auto it2 = trie.find("b");
	it2 = it1;
	EXPECT_TRUE(it1 == it2);
}
TEST(trie_iterator,handling_to_end_operator_star)
{
	Trie<int> trie;
	auto it = trie.end();
	try
	{
		*it;
	}
	catch (std::runtime_error& err)
	{
		EXPECT_TRUE(true);
		std::cout << "Runtime_error: " << err.what() << std::endl;
	}
}
TEST(trie_iterator, handling_to_end_operator_arrow)
{
	Trie<int> trie;
	auto it = trie.end();
	try
	{
		it->second;
	}
	catch (std::runtime_error& err)
	{
		EXPECT_TRUE(true);
		std::cout << "Runtime_error: " << err.what() << std::endl;
	}
}
TEST(trie_iterator, handling_to_end_operator_plus)
{
	Trie<int> trie;
	auto it = trie.end();
	try
	{
		it++;
	}
	catch (std::runtime_error& err)
	{
		EXPECT_TRUE(true);
		std::cout << "Runtime_error: " << err.what() << std::endl;
	}
}
TEST(trie_iterator, handling_to_end_plus_operator)
{
	Trie<int> trie;
	auto it = trie.end();
	try
	{
		++it;
	}
	catch (std::runtime_error& err)
	{
		EXPECT_TRUE(true);
		std::cout << "Runtime_error: " << err.what() << std::endl;
	}
}
TEST(trie_insert_delete,insert_same_key)
{
	Trie<int> trie;
	trie.insert("a", 4);
	trie.insert("a", 5);
	EXPECT_TRUE(trie.find("a")->second == 5);
}
TEST(trie_erase,erase_not_exisiting_element)
{
	Trie<int> trie;
	trie.insert("a", 4);
	trie.erase("b");
	EXPECT_TRUE(trie.size() == 1);
	EXPECT_TRUE(trie.begin()->first == "a");
}
TEST(trie_structure,equate)
{
	Trie<int> trie;
	fill_trie(trie);
	Trie<int> another_trie;
	trie = another_trie;
	EXPECT_TRUE(trie.empty());
	another_trie.insert("a", 21);
	EXPECT_TRUE(trie.find("a") == trie.end());
}

TEST(trie_structure, constructor) {
	const Trie<int> trie;
	EXPECT_TRUE(trie.empty());
}
TEST(trie_insert_delete,insert_1_delete_1)
{
	Trie<int> trie;
	trie.insert(keys[0], 1);
	EXPECT_TRUE(trie[keys[0]] == 1);
	trie.erase(keys[0]);
	EXPECT_TRUE(trie.empty());
	EXPECT_TRUE(trie.find(keys[0]) == trie.end());
}
TEST(trie_iterator, operator_plus_plus)
{
	Trie<int> trie;
	trie.insert("a", 4);
	trie.insert("b", 4);
	auto it = trie.find("a");
	auto temp = it++;
	EXPECT_TRUE(it->first == "b");
	EXPECT_TRUE(temp->first == "a");
}
TEST(const_trie_iterator, operator_plus_plus)
{
	Trie<int> trie;
	trie.insert("a", 4);
	trie.insert("b", 4);
	auto it = trie.cfind("a");
	auto temp = it++;
	EXPECT_TRUE(it->first == "b");
	EXPECT_TRUE(temp->first == "a");
}
TEST(trie_iterator,begin)
{
	Trie<int> trie;
	auto it = trie.begin();
	EXPECT_TRUE(it == trie.end());
	trie.insert(keys[0], 1);
	auto first = trie.begin();
	EXPECT_TRUE((*first).first==keys[0]);
}
TEST(trie_iterator,operator_arrow)
{
	Trie<int> trie;
	fill_trie(trie);
	size_t count = 0;
	auto it = trie.begin();
	std::vector <std::string> checked_keys(keys);
	for (auto t = trie.begin(); t != trie.end(); ++t)
	{
		count++;
		auto found = std::find(checked_keys.begin(), checked_keys.end(), (*t).first);
		EXPECT_TRUE(t->first == *found);
		checked_keys.erase(found);
	}
	EXPECT_TRUE(checked_keys.empty());
	EXPECT_TRUE(count == keys.size());

}
TEST(const_trie_iterator, operator_arrow)
{
	Trie<int> trie;
	fill_trie(trie);
	size_t count = 0;
	auto it = trie.begin();
	std::vector <std::string> checked_keys(keys);
	for (auto t = trie.cbegin(); t != trie.cend(); ++t)
	{
		count++;
		auto found = std::find(checked_keys.begin(), checked_keys.end(), (*t).first);
		EXPECT_TRUE(t->first == *found);
		checked_keys.erase(found);
	}
	EXPECT_TRUE(checked_keys.empty());
	EXPECT_TRUE(count == keys.size());

}
TEST(trie_iterator,end)
{
	Trie<int> trie;
	auto it = trie.end();
	EXPECT_TRUE(it == trie.begin());
}
TEST(trie_iterator, plus_plus_operator){
	std::map<const std::string, int> map;
	Trie<int> trie;
	fill_trie(trie);
	fill_map(map);
	auto m = map.begin();
	for (auto t = trie.begin();t!=trie.end();++t)
	{
		EXPECT_TRUE(m->first == (*t).first);
		++m;
	}
}
TEST(trie_iterator,operatot_equality)
{
	Trie<int> trie;
	trie.insert("a", 1);
	auto it1 = trie.find("a");
	auto it2 = trie.find("a");
	EXPECT_TRUE(it1 == it2);
}
TEST(const_trie_iterator, operatot_equality)
{
	Trie<int> trie;
	trie.insert("a", 1);
	auto it1 = trie.cfind("a");
	auto it2 = trie.cfind("a");
	EXPECT_TRUE(it1 == it2);
}
TEST(trie_iterator,go_through_trie)
{
	Trie<int> trie;
	fill_trie(trie);
	size_t count = 0;
	std::vector <std::string> checked_keys(keys);
	for (auto t = trie.begin(); t != trie.end(); ++t)
	{
		count++;
		auto found = std::find(checked_keys.begin(), checked_keys.end(), (*t).first);
		EXPECT_TRUE((*t).first == *found);
		checked_keys.erase(found);
	}
	EXPECT_TRUE(checked_keys.empty());
	EXPECT_TRUE(count == keys.size());
	
}
TEST(const_trie_iterator, begin)
{
	Trie<int> trie;
	auto it = trie.cbegin();
	EXPECT_TRUE(it == trie.cend());
	trie.insert(keys[0], 1);
	auto first = trie.cbegin();
	EXPECT_TRUE((*first).first == keys[0]);
}

TEST(const_trie_iterator, end)
{
	Trie<int> trie;
	auto it = trie.cend();
	EXPECT_TRUE(it == trie.cbegin());
}

TEST(const_trie_iterator,plus_plus_operator) {
	std::map<const std::string, int> map;
	Trie<int> trie;
	fill_trie(trie);
	fill_map(map);
	auto m = map.begin();
	for (auto t = trie.cbegin(); t != trie.cend(); ++t)
	{
		EXPECT_TRUE(m->first == (*t).first);
		++m;
	}
}

TEST(const_trie_iterator, go_through_trie)
{
	Trie<int> trie;
	fill_trie(trie);
	size_t count = 0;
	std::vector <std::string> checked_keys(keys);
	for (auto t = trie.cbegin(); t != trie.cend(); ++t)
	{
		count++;
		auto found = std::find(checked_keys.begin(), checked_keys.end(), (*t).first);
		EXPECT_TRUE((*t).first == *found);
		checked_keys.erase(found);
	}
	EXPECT_TRUE(checked_keys.empty());
	EXPECT_TRUE(count == keys.size());
}

TEST(trie_insert_delete, insert_110_delete_110)
{
	Trie<int> trie;
	fill_trie(trie);
	EXPECT_TRUE(trie.size() == keys.size());
	for (auto t = trie.begin(); t != trie.end();)
	{
		auto current = t++;
		trie.erase(current);
	}
	EXPECT_TRUE(trie.empty());
}

TEST(trie_searching, find)
{
	Trie<int> trie;
	fill_trie(trie);
	for (auto it = keys.begin(); it != keys.end(); ++it)
	{
		EXPECT_TRUE(trie.find(*it) != trie.end());
	}

}
TEST(trie_searching, cfind)
{
	Trie<int> trie;
	fill_trie(trie);
	for (auto it = keys.begin(); it != keys.end(); ++it)
	{
		
		EXPECT_TRUE(trie.cfind(*it) != trie.cend());
	}
	//trie.cbegin()->second = 32;  - don't work

}
TEST(trie_searching, operator_square_brackets)
{
	Trie<int> trie;
	fill_trie(trie);
	int value;
	for (auto it = keys.begin(); it != keys.end(); ++it)
	{
		value = trie[*it];
		EXPECT_TRUE(keys[value] == (*trie.find(*it)).first);
	}

}


TEST(trie_erase,erase_by_key)
{
	Trie<int> trie;
	fill_trie(trie);
	trie.erase(keys[34]);
	EXPECT_TRUE(trie.size() == keys.size() - 1);
	EXPECT_TRUE(trie.find(keys[34]) == trie.end());
}

TEST(trie_erase, erase_by_iterator)
{
	Trie<int> trie;
	fill_trie(trie);
	trie.erase(keys[34]);
	EXPECT_TRUE(trie.size() == keys.size() - 1);
	EXPECT_TRUE(trie.find(keys[34]) == trie.end());
}

TEST(trie_erase, erase_from_first_to_last)
{
	Trie<int> trie;
	trie.insert("a", 1);
	trie.insert("aa", 1);
	trie.insert("b", 1);
	auto first = trie.find("a");
	auto last = trie.find("aa");
	trie.erase(first, last);
	EXPECT_TRUE(trie.size() == 1);
	EXPECT_TRUE((*trie.begin()).first == "b");
	
}
TEST(trie_erase, clear)
{
	Trie<int> trie;
	fill_trie(trie);
	trie.clear();
	EXPECT_TRUE(trie.empty());
	EXPECT_TRUE(trie.begin() == trie.end());
}


static void fill_special_trie(Trie<std::vector<std::string>>& trie)
{
	for (size_t i = 0; i < keys.size(); i++)
	{
		trie.insert(keys[i], keys);
	}
}

TEST(trie_contains_another_class,insert_delete)
{
	Trie<std::vector<std::string>> trie;
	fill_special_trie(trie);
	EXPECT_TRUE(trie.size() == keys.size());
	for (auto t = trie.begin(); t != trie.end();)
	{
		auto current = t++;
		trie.erase(current);
	}
	EXPECT_TRUE(trie.empty());
}
TEST(trie_contains_another_class, find)
{
	Trie<std::vector<std::string>> trie;
	fill_special_trie(trie);
	EXPECT_TRUE(trie.size() == keys.size());
	for (auto t = trie.begin(); t != trie.end();++t)
	{
		auto found = trie.find(t->first);
		EXPECT_TRUE(found != trie.end());
	}
}
TEST(trie_contains_another_class, operator_arrow)
{
	Trie<std::vector<std::string>> trie;
	fill_special_trie(trie);
	auto it = trie.begin();
	EXPECT_TRUE(it->second[0] == keys[0]);
}
TEST(trie_contains_another_class, operator_star)
{
	Trie<std::vector<std::string>> trie;
	fill_special_trie(trie);
	auto it = trie.begin();
	EXPECT_TRUE((*it).second[0] == keys[0]);
}
GTEST_API_ int main(int argc, char * argv[])
{																													
	if (argc > 0)
	{
		testing::internal::FilePath arg(argv[0]);
		const auto name = arg.RemoveDirectoryName().RemoveExtension("exe").string();
		testing::GTEST_FLAG(output) = std::string("xml:") + name + ".xml";
	}
	testing::InitGoogleTest(&argc, argv);
#if defined(_MSC_VER)
	testing::UnitTest::GetInstance()->listeners().Append(new testing::MSVCMemoryLeakListener());
#endif // defined(_MSC_VER)
	return RUN_ALL_TESTS();
}



