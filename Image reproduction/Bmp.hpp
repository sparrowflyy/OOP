#pragma once
#include "libbitmap.h"

class bmp :public Bitmap {
public:
	bmp();
	bmp(const char* bmp_file_name);
	bmp(const char* size_file_name, const char* export_name);
	bmp(size_t width, size_t height, const char* export_name);
	~bmp();

	void reproduction(const bmp& patteren);

	template < size_t _align >
	size_t _align_size(size_t s) const;
	inline size_t _get_stride() const;
	inline size_t _get_line_size() const;
	inline size_t _get_pixel_array_size() const;
protected:
	char* init_name(char* dst, size_t dstSize, const char* pattern_name);
private:
	Bitmap bmp_image;
	const char* bmp_name;
};