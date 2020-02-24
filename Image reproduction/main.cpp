#include "Bmp.hpp"


int main() {
	const char* pattern_name = "pattern.bmp";
	const char* export_name = "result.bmp";
	bmp pat(pattern_name);
	bmp& pattern = pat;
	bmp rep(998, 999, nullptr);
	rep.reproduction(pattern);
}