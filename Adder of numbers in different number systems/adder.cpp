#include "adder.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <cmath>
#include <deque>

Number::Number() {
	base = 0;
	d_number = 0;
	digits.clear();
}
Number::Number(int _base, std::vector<int>& dig ) {
	if (_base < 2 || dig.size()<0 ) Number();
	else {
		d_number = 0;
		base = _base;
		digits.insert(digits.cend(), dig.cbegin(), dig.cend());
	}
}
Number::~Number(){
	digits.clear();
}

Number Number::to_decimal(const Number& a){
	if (a.digits.size() == 0) return Number();
	size_t size =a.digits.size();
	long long sum=0;
	long long tmp;
	for (int i = 0; i < size; i++) {
		tmp = a.digits[i] * pow(a.base, size - 1 - i);
		sum += tmp;
	}
	std::vector<int> new_digits;
	char buf[25];
	sprintf(buf, "%lli", sum);
	char ch=0; int digit; int i = 0;
	while (1) {
		ch = buf[i];
		if (ch == '\0') break;
		digit = ch - '0';
		new_digits.push_back(digit);
		i++;

	}
	Number new_number(10, new_digits);
	new_number.d_number = sum;
	return new_number;
}

Number Number::to_base(const Number& a,int new_base) { 
	if (new_base < 2 || a.digits.size() == 0) return Number();
	Number new_number=a.to_decimal(a);
	std::deque<int> rest;					
	long long  res,res_number=new_number.d_number;
	new_number.digits.clear();
	if (new_number.d_number != 0) {
		while (res_number) {
			res = res_number % new_base;
			res_number = res_number / new_base;
			rest.push_front(res);
		}
		new_number.digits.insert(new_number.digits.cend(), rest.cbegin(), rest.cend());
	}
	rest.clear();
	new_number.base = new_base;
	return new_number;
}


Number Number::plus(const Number& A, const Number& B, int new_base) {
	if (new_base < 2 || A.digits.size() == 0 || B.digits.size() == 0) return Number();
	Number C1 = Number::to_base(A, new_base);
	Number C2 = Number::to_base(B, new_base);
	std::reverse(C1.digits.begin(), C1.digits.end());
	std::reverse(C2.digits.begin(), C2.digits.end());
	std::deque<int> result;
	 int tmp = 0, res = 0, max_size;
	int size1 = C1.digits.size();
	int size2 = C2.digits.size();
	if (size1 > size2) max_size = size1;
	else max_size = size2;
	for (int i = 0; i < max_size; i++) {
		if (i<size1 && i<size2) {
			tmp = C1.digits[i] + C2.digits[i] + res;
			if (tmp < new_base) {
				result.push_front(tmp);
				res = 0;
			}
			else {
				result.push_front(tmp - new_base);
				res = 1;
			}
		}
		else if (max_size == size1) {
			tmp = C1.digits[i] + res;
			if (tmp < new_base) {
				result.push_front(tmp);
				res = 0;
			}
			else {
				result.push_front(tmp - new_base);
				res = 1;
			}
		}
		else {
			tmp = C2.digits[i] + res;
			if (tmp < new_base) {
				result.push_front(tmp);
				res = 0;
			}
			else {
				result.push_front(tmp-new_base);
				res = 1;
			}
		}
	}
	if (res != 0) result.push_front(1);
	std::vector<int> result_digits;
	for (auto it = result.cbegin();it!=result.cend(); ++it) {
		result_digits.push_back(*it);
		
	}
	Number summa(new_base,result_digits);
	return summa;
}
Number Number::parser(std::string s) {      
	if (s.size() < 4 || s.find(':',0)==s.npos || s.find('"')==s.npos) return Number();
	int base_digit = std::stoi(s);
	if (base_digit < 2) return Number();
	std::vector<int> Digits;
	size_t pos = s.find_first_of('\"', 0);
	if (pos == s.npos) return Number();
	size_t pos1 =s.find_first_of('\"', pos+1);
	size_t len = (pos1 == s.npos) ? s.npos : pos1 - pos-1;
	if (len == 0) return Number();
	std::string digit(s.substr(pos+1, len));
	char c;
	for (auto it = digit.begin(); it != digit.end(); ++it) {
		if (isdigit(*it) == 0) {
			if (islower(*it) == 0) Digits.push_back(*it - 'a');
			else Digits.push_back(*it - 'A');

		}
		else Digits.push_back(*it - '0');
	}

	Number r_number(base_digit, Digits);
	return r_number;
}
Number Number::plus(const char* file_name) {
	if (file_name == nullptr) return Number();
	std::ifstream file(file_name);
	Number A; Number B;
	if (file) {
		std::string buffer;
		getline(file, buffer);
		A = Number::parser(buffer);
		getline(file, buffer);
		B=  Number::parser(buffer);
		getline(file, buffer);
		int new_base = std::stoi(buffer);
		if (new_base < 2 || new_base>36) return Number();
		buffer.clear();
		return Number::plus(A,B,new_base);
		}
	else return Number();
	}
std::string Number::digits_to_string(const Number& a) {
	std::stringstream ss;
	std::string str_dig;
	std::copy(a.digits.cbegin(), a.digits.cend(), std::ostream_iterator<int>(ss,""));
	ss >> str_dig;
	return str_dig;
}
void Number::write_to_file(const char* filename) const { 
	if (filename == nullptr || digits.size() == 0) return;
	std::ofstream fout(filename);
	fout << base << ":\"";
	fout << Number::digits_to_string(*this);
	fout << "\"";
	fout.close();
}
Number Number::read_number(const char* filename) {
	if (filename == nullptr) return Number();
	std::ifstream file(filename);
	std::string buffer;
	getline(file, buffer);
	Number result = parser(buffer);
	file.close();
	return result;
}