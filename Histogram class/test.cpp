#include ".//gtest/gtest.h"
#include "..//histogram/histogram.hpp"
std::vector<std::string> book = { "1","2","3","1","4","5","A","B","A","Histogram","1" };
TEST(Method_test_constuctors, istream_cons) {
	std::stringstream ss1("1 2 3 4 2 3 1 4 5 1");
	std::stringstream ss2("one two three four two three one four five one");
	Histogram hist1(ss1);
	Histogram hist2(ss2);
	std::map<const std::string, int> result1 = { {"1", 3}, {"2", 2}, {"3", 2}, {"4", 2}, {"5", 1} };
	EXPECT_TRUE(result1==hist1.get_hist());
	std::map<const std::string, int> result2 = { {"one", 3}, {"two", 2}, {"three", 2}, {"four", 2}, {"five", 1} };
	EXPECT_TRUE(result2==hist2.get_hist());
}
TEST(Method_test_constuctors, vector_cons) {
	Histogram hist(book);
	const std::map<const std::string, int> result = { {"1",3},{"2",1},{"3",1},{"4",1},{"5",1},{"A",2},{"B",1},{"Histogram",1} };
	EXPECT_TRUE(result== hist.get_hist());
}
TEST(Operator_test, operator_eq) {
	Histogram hist1(book);
	Histogram hist2(book);
	EXPECT_TRUE(hist1 == hist2);

}
TEST(Method_test_constuctors, copy_cons) {
	Histogram hist1(book);
	Histogram hist2(hist1);
	EXPECT_TRUE(hist1 == hist2);
}
TEST(Operator_test, operator_plus) {
	Histogram hist1(book);
	std::stringstream another_book("1 6 2 5 Another_histogram 4 C 3 1");
	Histogram hist2(another_book);
	Histogram sum = hist1 + hist2;
	std::map<const std::string, int> result = { {"1",5},{"2",2},{"3",2},{"4",2},{"5",2},{"A",2},{"B",1},{"Histogram",1},{"6",1},{"Another_histogram", 1},{"C", 1} };
	//const auto& res = sum.get_hist();
	EXPECT_EQ(result, sum.get_hist());
	hist1 += hist2;
	EXPECT_EQ(result,hist1.get_hist());
}
TEST(Operator_test, operator_minus) {
	Histogram hist1(book);
	std::stringstream another_book("1 6 2 5 Another_histogram 4 C 3 1");
	Histogram hist2(another_book);
	Histogram dif = hist1 - hist2;
	std::map<const std::string, int> result = { {"1",1},{"2",0},{"3",0},{"4",0},{"5",0},{"A",2},{"B",1},{"Histogram",1},{"C",-1}, {"6",-1},{"Another_histogram",-1} };
	EXPECT_EQ(result, dif.get_hist());
	hist1 -= hist2;
	EXPECT_EQ(result,hist1.get_hist());
}
TEST(Iterator_test, empty) {
	Histogram empty;
	EXPECT_TRUE(empty.begin() == empty.end());
}
TEST(Iterator_test, begin_end) {
	Histogram hist(book);
	EXPECT_TRUE(hist.begin()!=hist.end());
	const std::map<const std::string, int> result = { {"1",3},{"2",1},{"3",1},{"4",1},{"5",1},{"A",2},{"B",1},{"Histogram",1} };
	auto it2 = result.begin();
	size_t count = 0;
	for (auto it1 = hist.begin(); it1 != hist.end() && it2!=result.end(); ++it1) {
		const std::pair<const std::string, int>& element = *it1;
		const std::pair<const std::string, int>& element_result = *it2;
		EXPECT_EQ((element.first),(element_result.first));
		++it2;
		count++;
	}	
	EXPECT_EQ(count, result.size());
	for (auto it = hist.begin(); it != hist.end(); ++it) {
		const auto& element = *it;
		EXPECT_TRUE(result.find(element.first) != result.end());
	}
}
