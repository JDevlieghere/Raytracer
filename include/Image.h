#pragma once

#include "Pixel.h"

class Image {
public:
	Image(unsigned int width, unsigned int height);

	const Pixel& getPixel(unsigned int x, unsigned int y) const;
	void setPixel(unsigned int x, unsigned int y, const Pixel& pixel);

	unsigned int getWidth() const;
	unsigned int getHeight() const;

private:
	unsigned int getIndex(unsigned int x, unsigned int y) const;
	unsigned int _width;
	unsigned int _height;
	Pixel* _pixels;
};