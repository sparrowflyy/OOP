#include "gtest/gtest.h"
#include "../adder/adder.hpp"
const char* filename = "test.txt";

std::vector<int> digits2{ 1,0 };	//2				//переполнение
std::vector<int> digits3{ 2,1,0 };	//21
std::vector<int> digits4{ 3,2,1,0 }; //228
std::vector<int> digits5{ 4,3,2,1,0 }; //2930
std::vector<int> digits6{ 5,4,3,2,1,0 }; //44790
std::vector<int> digits7{ 6,5,4,3,2,1,0 }; //800667
std::vector<int> digits8{ 7,6,5,4,3,2,1,0 }; //16434824
std::vector<int> digits9{ 8,7,6,5,4,3,2,1,0 }; //381367044
std::vector<int> digits10{ 9,8,7,6,5,4 }; //987654
std::vector<int> digits11{ 10,9,8,7,6,5 }; //1753845
std::vector<int> digits12{ 11,10,9,8,7,6 }; //2961306
std::vector<int> digits13{ 12,11,10,9,8,7 }; //4793289
std::vector<int> digits14{ 13,12,11,10,9,8 }; //7484982
std::vector<int> digits15{ 14,13,12,11,10,9 }; //11332509
std::vector<int> digits16{ 15,14,13,12,11,10 }; //16702650

std::vector<int> bases{ 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
std::vector<long long> decimal_numbers{ 2,21,228,2930,44790,800667,16434824,381367044,987654,1753845,2961306,4793289,7484982,11332509,16702650 };

Number number2(bases[0], digits2);
Number number3(bases[1], digits3);
Number number4(bases[2], digits4);
Number number5(bases[3], digits5);
Number number6(bases[4], digits6);
Number number7(bases[5], digits7);					//9999999+1  
Number number8(bases[6], digits8);					//10101010101+0101010101
Number number9(bases[7], digits9);
Number number10(bases[8], digits10);
Number number11(bases[9], digits11);
Number number12(bases[10], digits12);
Number number13(bases[11], digits13);
Number number14(bases[12], digits14);
Number number15(bases[13], digits15);
Number number16(bases[14], digits16);

std::vector<Number> Numbers{ number2,number3,number4,number5,number6,number7,number8,number9,number10,number11,number12,number13,number14,number15,number16 };
TEST(Incorrect_data, incorrect_data) {
	Number test_number;
	test_number = Number::to_base(number2, 1);
	EXPECT_TRUE(test_number.digits.size()==0 && test_number.base==0);

	test_number = Number::to_base(number2, -5);
	EXPECT_TRUE(test_number.digits.size() == 0 &&  test_number.base == 0);

	test_number = Number::to_decimal(test_number);
	EXPECT_TRUE(test_number.digits.size() == 0 &&  test_number.base == 0);

	test_number = Number::plus(test_number,number2, 10);
	EXPECT_TRUE(test_number.digits.size() == 0 && test_number.base == 0);

	test_number = Number::plus(filename);
	EXPECT_TRUE(test_number.digits.size() == 0 && test_number.base == 0);
}


TEST(Number_function, to_decimal) {
	Number tmp;
	size_t size = Numbers.size();
	for (int i = 0; i < size;i++) {
		tmp = Number::to_decimal(Numbers[i]);
		EXPECT_EQ(tmp.d_number, decimal_numbers[i]);
	}
}

TEST(Number_functions, to_base) {
	Number tmp;
	size_t size_n = Numbers.size();
	size_t size_b = bases.size();
	for (int i = 0; i < size_n; i++) {
		for (int j = 0; j < size_b; j++) {
			tmp = Number::to_base(Numbers[i],bases[j]);
			tmp = Number::to_decimal(tmp);
			EXPECT_EQ(tmp.d_number, decimal_numbers[i]);
		}
	}
}

TEST(Number_functions, plus) {
	Number tmp;
	size_t size_n = Numbers.size();
	size_t size_b = bases.size(); 
	for (int i = 0; i < size_n - 1; i++) {
		for (int j = 0; j < size_b; j++) {
			tmp = Number::plus(Numbers[i],Numbers[i + 1], bases[j]);
			tmp = Number::to_decimal(tmp);
			EXPECT_EQ(tmp.d_number, decimal_numbers[i] + decimal_numbers[i + 1]);
		}
	}
	

}
TEST(Number_functions, plus_special_test) {
	std::vector<int> first_digits = { 1,0,1,0,1,0 };
	std::vector<int> second_digits = { 0,1,0,1,0,1 };
	Number first(2, first_digits);
	Number second(2, second_digits);
	Number summa = Number::plus(first, second, 2);
	for (auto it = summa.digits.begin(); it != summa.digits.end(); ++it) {
		EXPECT_EQ(1, *it);
	}
	std::vector<int> nine_digits = { 9,9,9,9,9,9};
	std::vector<int> one = { 1 };
	Number big(10, nine_digits);
	Number small(10, one);
	Number sum = Number::plus(big, small, 10);
	EXPECT_EQ(1, sum.digits[0]);
	for (int i = 1; i < sum.digits.size();i++) {
		EXPECT_EQ(0, sum.digits[i]);
	}
}
TEST(Number_functions, plus_from_file) { 
	Number A = Number::plus("summa.txt");
	Number B = Number::plus(Numbers[0],Numbers[1], 6);
	EXPECT_TRUE(A.digits == B.digits);
}
TEST(Number_functions, write_from_file) { 
	Numbers[2].write_to_file("Number2.txt");
	Numbers[3].write_to_file("Number3.txt");
	Number second = Number::read_number("Number2.txt");
	Number third = Number::read_number("Number3.txt");
	EXPECT_EQ(Numbers[2].digits, second.digits);
	EXPECT_EQ(Numbers[2].base, second.base);
	EXPECT_EQ(Numbers[3].digits, third.digits);
	EXPECT_EQ(Numbers[3].base, third.base);
}