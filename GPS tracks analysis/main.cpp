#include "GPS.hpp"
#include <iostream>
int main() {
	GPStrack test("50467.gpx");
	std::ofstream result;
	result.open("RESULT.txt");
	test.print_result(result);
	

}