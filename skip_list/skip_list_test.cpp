#include "./gtest/gtest.h"
#include "my_skip_list.hpp"

static const int big_size = 100;
TEST(skip_list,copy_constructor)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	skip_list<const int, int> copied_list(test_list);
	EXPECT_TRUE(copied_list == test_list);
	test_list.insert({ 4124,2342 });
	EXPECT_TRUE(copied_list != test_list);
}
TEST(skip_list, operator_equating)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	skip_list<const int, int> copied_list=test_list;
	EXPECT_TRUE(copied_list == test_list);
	test_list.insert({ 4124,2342 });
	EXPECT_TRUE(copied_list != test_list);
}
TEST(skip_list,swap)
{
	skip_list<const int, int> test_list1;
	for (int i = 0; i != big_size; i++)
	{
		test_list1.insert({ i,i });
	}
	skip_list<const int, int> test_list2;
	test_list2.insert({ 666,666 });
	test_list1.swap(test_list2);
	EXPECT_TRUE(test_list1.size() == 1);
	auto begin = test_list1.begin();
	EXPECT_TRUE((*begin).first == 666);
	EXPECT_TRUE(test_list2.size() == big_size);
	test_list2.insert({ -4,-5 });
	EXPECT_EQ(-5, test_list2.at(-4));
	for (int i = 0; i != big_size; i++)
	{
		EXPECT_EQ(i, test_list2.at(i));
	}
	
}
TEST(skip_list,operator_compare)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	skip_list<const int, int> another_list;
	for (int i = 0; i != big_size; i++)
	{
		another_list.insert({ i,i });
	}
	EXPECT_TRUE(test_list == another_list);
	another_list.insert({ -1,-1 });
	EXPECT_TRUE(test_list != another_list);
}
TEST(skip_list_insert, insert_1) {
	skip_list<const char, int> test_list;
	test_list.insert({ 'A',666 });
	EXPECT_EQ(666, test_list.at('A'));
	EXPECT_EQ(test_list.size(),1);
}
TEST(skip_list_insert,insert_big_size) {
	skip_list<const int, int> test_list;
	for (int i = 0; i!= big_size;i++)
	{
		test_list.insert({ i,i });
	}
	for (int i = 0; i != big_size; i++)
	{
		EXPECT_EQ(i, test_list.at(i));
	}
	EXPECT_EQ(test_list.size(), big_size);
}
TEST(skip_list_insert_delete, insert_delete_1) {
	skip_list<const char, int> test_list;
	test_list.insert({ 'A',666 });
	EXPECT_EQ(666, test_list.at('A'));
	EXPECT_EQ(test_list.size(), 1);
	test_list.erase('A');
	try {
		int test = test_list.at('A');
	}
	catch(const char c)
	{
		EXPECT_TRUE(c == 'A');
	}
	EXPECT_EQ(0, test_list.size());
}
TEST(skip_list_insert_delete, insert_delete_big_size)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	for (int i = 0; i != big_size; i++)
	{
		EXPECT_EQ(i, test_list.at(i));
	}
	EXPECT_EQ(test_list.size(), big_size);
	for (int i = 0; i != big_size; i++)
	{
		test_list.erase(i);
		try {
			test_list.at(i);
		}
		catch(const int thrown)
		{
			EXPECT_EQ(thrown, i);
		}
		EXPECT_EQ(big_size -i-1, test_list.size());
	}
}
TEST(skip_list_insert_delete, erase_iterator)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	for (int i = 0; i != big_size; i++)
	{
		EXPECT_EQ(i, test_list.at(i));
	}
	EXPECT_EQ(test_list.size(), big_size);
	test_list.erase(test_list.find(0));
	auto it = test_list.begin();
	EXPECT_TRUE((*it).second==1);
}
TEST(skip_list_insert_delete, erase_iterator_diaposone)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	for (int i = 0; i != big_size; i++)
	{
		EXPECT_EQ(i, test_list.at(i));
	}
	EXPECT_EQ(test_list.size(), big_size);
	test_list.erase(test_list.find(1),test_list.find(99));
	auto it = test_list.begin();
	EXPECT_TRUE((*it).second == 0);
	++it;
	EXPECT_TRUE(it == test_list.end());
}
TEST(skip_list_insert_delete, clear)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	for (int i = 0; i != big_size; i++)
	{
		EXPECT_EQ(i, test_list.at(i));
	}
	test_list.clear();
	EXPECT_TRUE((int)test_list.size() == 0);
	EXPECT_TRUE(test_list.begin() == test_list.end());
}
TEST(skip_list_insert_delete, erase_non_existing)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	size_t size = test_list.size();
	for (int i = 0; i != big_size; i++)
	{
		test_list.erase(i + big_size);
		EXPECT_EQ(i, test_list.at(i));
	}

	EXPECT_TRUE(test_list.size() == size);
}
TEST(skip_list_iterator,begin_end)
{
	skip_list<const char, int> test_list;
	auto begin1 = test_list.begin();
	auto end = test_list.end();
	EXPECT_EQ(begin1, end);
	test_list.insert({ 'A',666 });
	auto begin2 = test_list.begin();
	EXPECT_EQ((*begin2).second, 666);
}
TEST(skip_list_iterator,equating)
{
	skip_list<const char, int> test_list;
	test_list.insert({ 'A',666 });
	test_list.insert({ 'B',666 });
	skip_list<const char,int>::sklist_iterator it_1 = test_list.find('A');
	skip_list<const char, int>::sklist_iterator it_2 = test_list.find('B');
	skip_list<const char, int>::sklist_iterator it_3;
	it_3 = it_1;
	EXPECT_TRUE((*it_3).first == 'A');
	it_3 = it_2;
	EXPECT_TRUE((*it_3).first == 'B');
	
}
TEST(skip_list_iterator, operator_asterisk)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	int k = 0;
	for (auto it = test_list.begin();it!=test_list.end();++it)
	{
		EXPECT_TRUE((*it).first == k);
		EXPECT_TRUE((*it).second == k);
		k++;
	}
}

TEST(skip_list_iterator,running_through)
{
	skip_list<const int, int> test_list;
	for (int i = 0; i != big_size; i++)
	{
		test_list.insert({ i,i });
	}
	int i = 0;
	for (auto it = test_list.begin(); it!=test_list.end();++it)
	{
		EXPECT_EQ(i, (*it).first);
		i++;
	}
}
TEST(skip_list_iterator,operator_is_equal)
{
	skip_list<const char, int> test_list;
	test_list.insert({ 'A',666 });
	auto begin1 = test_list.begin();
	auto begin2 = test_list.begin();
	EXPECT_TRUE(begin1 == begin2);
	test_list.insert({ 'B',666 });
	auto iter = test_list.find('B');
	EXPECT_FALSE(begin1 == iter);
	EXPECT_FALSE(begin2 == iter);
}
TEST(skip_list_iterator,operator_is_not_equal)
{
	skip_list<const char, int> test_list;
	test_list.insert({ 'A',666 });
	test_list.insert({ 'B',666 });
	auto iter = test_list.find('B');
	auto begin1 = test_list.begin();
	auto begin2 = test_list.begin();
	EXPECT_FALSE(begin1 != begin2);
	EXPECT_TRUE(begin1 != iter);
	EXPECT_TRUE(begin2 != iter);
}
TEST(skip_list_iterator, cbegin_cend)
{
	const skip_list<const char, int> const_test_list;
	auto cbegin1 = const_test_list.cbegin();
	auto cend = const_test_list.cend();
	EXPECT_EQ(cbegin1, cend);

	skip_list<const char, int> test_list;
	test_list.insert({ 'A',666 });
	test_list.insert({ 'F',43 });
	const skip_list<const char, int> another_const_list=test_list;
	test_list.insert({'V', 123});
	auto cbegin2 = another_const_list.cbegin();
	auto cend2 = another_const_list.cend();
	EXPECT_EQ((*cbegin2).second, 666);
	EXPECT_TRUE(cbegin2!=cend2);
}

TEST(skip_list_searching,find_cfind_element)
{
	skip_list<const int, int> list;
	for (int i = 0; i != big_size; i++)
	{
		list.insert({ i,i });
	}
	const skip_list<const int, int> const_list=list;
	auto iter = list.find(99);
	EXPECT_EQ((*iter).second, 99);
	auto citer = const_list.cfind(99);
	EXPECT_EQ((*citer).second, 99);
}
TEST(skip_list_searching, find_cfind_non_existing_element)
{
	skip_list<const int, int> list;
	for (int i = 0; i != big_size; i++)
	{
		list.insert({ i,i });
	}
	const skip_list<const int, int> const_list = list;
	auto iter = list.find(123);
	EXPECT_TRUE(iter == list.end());
	auto citer = const_list.cfind(123);
	auto cnode = const_list.cfind(38);
	EXPECT_TRUE(citer == const_list.cend());
}
TEST(skip_list_searching,at_const_at)
{
	skip_list<const int, int> list;
	for (int i = 0; i != big_size; i++)
	{
		list.insert({ i,i });
	}
	const skip_list<const int, int> const_list=list;
	int val;
	
	for (int i = 0; i != big_size; i++)
	{
		val = list.at(i);
		EXPECT_EQ(val,i);
		const int cval = const_list.at(i);
		EXPECT_EQ(cval, i);
	}
	
}
TEST(skip_list_searching, at_const_at_non_existing_element)
{
	skip_list<const int, int> list;
	for (int i = 0; i != big_size; i++)
	{
		list.insert({ i,i });
	}
	const skip_list<const int, int> const_list = list;
	try {
		int val = list.at(123);
	}
	catch (const int thrown)
	{
		EXPECT_EQ(thrown, 123);
	}
	try {
		const int cval = const_list.at(123);
	}
	catch (const int thrown)
	{
		EXPECT_EQ(thrown, 123);
	}
}
TEST(skip_list_searching,operator_square_brackets)
{
	skip_list<const int, int> list;
	for (int i = 0; i != big_size; i++)
	{
		list.insert({ i,i });
	}
	const skip_list<const int, int> const_list = list;
	int val;
	for (int i = 0; i != big_size; i++)
	{
		val = list[i];
		EXPECT_EQ(val, i);
		const int cval = const_list[i];
		EXPECT_EQ(cval, i);
	}
}
TEST(skip_list_searching, operator_square_brackets_insertion)
{
	skip_list<const int, int> list;
	list[-123] = 15;
	EXPECT_TRUE(list.size() == 1);
	EXPECT_EQ((list.begin()).operator*().second, 15);
}
TEST(skip_list, double_insert)
{
	skip_list<const int, int> test_list1;
	test_list1.insert({ 1,0 });
	EXPECT_EQ(test_list1.at(1), 0);
	std::pair<skip_list<const int,int>::sklist_iterator, bool> p = test_list1.insert({ 1,1 });
	EXPECT_FALSE(p.second);
	EXPECT_EQ((*(p.first)).first, 1);
	EXPECT_EQ((*(p.first)).second, 0);
	EXPECT_EQ(test_list1.at(1), 0);
}

TEST(skip_list_with_other_class,inserting)
{
	skip_list<const std::string, std::vector<int>> test_list;
	for (int i = 0; i != big_size; i++)
	{
		
		const std::string key(std::to_string(i));
		std::vector<int> value={i};
		std::pair<const std::string, std::vector<int>> node_value(key, value);
		test_list.insert(node_value);
	}
	for (int i = 0; i != big_size; i++)
	{
		const std::string key(std::to_string(i));
		EXPECT_EQ(i, test_list.at(key)[0]);
	}
	EXPECT_EQ(test_list.size(), big_size);
}
TEST(skip_list_with_other_class,erasing)
{
	skip_list<std::string, std::vector<int>> test_list;
	char symbol = 'a';
	for (int i = 0; i != 50; i++)
	{
		
		std::string key;
		key.push_back(symbol);
		std::vector<int> value = { i };
		std::pair<const std::string, std::vector<int>> node_value(key, value);
		test_list.insert(node_value);
		symbol++;
	}
	symbol = 'a';
	for (int i = 0; i !=50; i++)
	{
		std::string key;
		key.push_back(symbol);
		test_list.erase(key);
		EXPECT_TRUE(test_list.find(key) == test_list.end());
		symbol++;
	}
	EXPECT_TRUE(test_list.begin() == test_list.end());
}
TEST(skip_list_with_other_class, iterators)
{
	skip_list<std::string, std::vector<int>> test_list;
	char symbol = 'a';
	for (int i = 0; i != 50; i++)
	{
		std::string key;
		key.push_back(symbol);
		std::vector<int> value = { i };
		std::pair<const std::string, std::vector<int>> node_value(key, value);
		test_list.insert(node_value);
		symbol++;
	}
	int i = 0;
	for (auto it = test_list.begin();it!=test_list.end();++it)
	{
		EXPECT_EQ((*it).second[0],i);
		i++;
	}	
}
