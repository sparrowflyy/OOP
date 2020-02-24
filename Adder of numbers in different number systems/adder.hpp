#pragma once
#include <vector>

	class Number {
	public:
		Number();
		Number(int _base, std::vector<int>& dig);
		~Number();
		static Number parser(std::string s);
		static std::string digits_to_string(const Number& a);
		static Number read_number(const char* filename);
		void write_to_file(const char* filename) const;
		static Number to_decimal(const Number& a);
		static Number to_base(const Number& a, int new_base);
		static Number plus(const Number& A, const Number& B, int new_base);
		static Number plus(const char* filename);

		long long d_number;
		int base;
		std::vector<int> digits;
	};
