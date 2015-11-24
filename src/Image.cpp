#include "Image.h"

Image::Image(unsigned int width, unsigned int height) : _width(width), _height(height) {}

const Pixel& Image::getPixel(unsigned int x, unsigned int y) const {
	return _pixels[getIndex(x,y)];
}

void Image::setPixel(unsigned int x, unsigned int y, const Pixel& pixel) {
	_pixels[getIndex(x, y)] = pixel;
}

unsigned int Image::getIndex(unsigned int x, unsigned int y) const {
	return y*_width + x;
}

unsigned int Image::getWidth() const {
	return _width;
}

unsigned int Image::getHeight() const {
	return _height;
}

