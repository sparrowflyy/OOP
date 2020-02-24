#include <fstream>
#include <iostream>
#include "Bmp.hpp"


template < size_t _align >
size_t bmp:: _align_size(size_t s) const
{
	return (_align & (_align - 1)) ?
		((s + _align - 1) / _align) * _align :  
		(s + _align - 1) & ~(_align - 1);        
}
inline size_t bmp:: _get_stride() const
{
	if (bmp_image.m_width > 0) return _align_size < 32 >(bmp_image.m_width * 24) >> 3;
	else return 0;
}
inline size_t bmp:: _get_line_size() const
{	
	if (bmp_image.m_width>0) return _align_size < 8 >(bmp_image.m_width * 24) >> 3;
	else return 0;
	
}
inline size_t bmp::_get_pixel_array_size() const
{
	if (bmp_image.m_width > 0 && bmp_image.m_height>0 )return _get_stride() * bmp_image.m_height;
	else return 0;
}
bmp::bmp() {
	bmp_name = nullptr;
	bmp_image.m_buffer = nullptr;
	bmp_image.m_height = 0;
	bmp_image.m_width = 0;
}
bmp::bmp(const char* bmp_file_name) {
	if (bmp_file_name == nullptr) {
		bmp();
	}
	else {
		bmp_image.load(bmp_file_name);
		bmp_name = new char[256];
		memcpy((char*)bmp_name, bmp_file_name, 256);
	}
}
char* bmp::init_name(char* dst ,size_t dstSize, const char* pattern_name) {
	memset((char*)dst, '\0', sizeof(char));
	sprintf_s(dst, dstSize, "%dx%d_%s", (int)bmp_image.m_width, (int)bmp_image.m_height, pattern_name);
	return dst;
}
bmp::bmp(const char* size_file_name, const char* export_name) {
	if (size_file_name == nullptr) bmp();
	else {
			if (export_name == nullptr) {
				bmp_name = nullptr;
			}
			else {
				bmp_name = new char[256];
				memcpy((char*)bmp_name, export_name, 256);
			}
			std::ifstream file;
			file.open(size_file_name);
			if (file) {
				file >> bmp_image.m_width;
				file >> bmp_image.m_height;
				bmp_image.m_buffer = new uint8_t[_get_pixel_array_size()];
				file.close();
			}
			else bmp();
	}
	
}
bmp::bmp(size_t width, size_t height, const char* export_name) {
	if (width <= 0 || height <= 0) bmp();
	else {
		if (export_name == nullptr) {
			bmp_name = nullptr;
		}
		else {
			bmp_name = new char[256];
			memcpy((char*)bmp_name, export_name, 256);
		}
		bmp_image.m_height = height;
		bmp_image.m_width = width;
		bmp_image.m_buffer = new uint8_t[_get_pixel_array_size()];

	}
}
bmp::~bmp() {
	delete[] bmp_name;
	bmp_image.clear();
}

void bmp::reproduction(const bmp& pattern) {
	if (bmp_image.m_buffer == nullptr || pattern.bmp_image.m_buffer == nullptr) return;

	size_t pattern_len = pattern._get_line_size();
	size_t bmp_len= _get_line_size();
	size_t plen_count = bmp_len / pattern_len;	

	size_t pattern_stride = pattern._get_stride();
	size_t bmp_stride = _get_stride();
	size_t additive = bmp_len % pattern_len;

	uint8_t* dst = bmp_image.m_buffer;
	uint8_t* src = pattern.bmp_image.m_buffer;

	for ( size_t y = 0; y < bmp_image.m_height; ++y)
	{
		dst = bmp_image.m_buffer + y * bmp_stride;
		for (size_t i = 0; i < plen_count; i++) {
			memcpy(dst, src, pattern_len);
			dst += pattern_len;
		}
		memcpy(dst, src, additive);
		if ((y + 1) % pattern.bmp_image.m_height == 0) {
			src = pattern.bmp_image.m_buffer;
		}
		else {
			src +=pattern_stride;
		}
	}
	if (bmp_name == nullptr) {
		bmp_name = new char[256];
		bmp_name = init_name((char*)bmp_name,256, pattern.bmp_name);
	}
	bmp_image.save(bmp_name);
}
