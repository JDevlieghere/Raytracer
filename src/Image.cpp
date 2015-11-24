#include "Image.h"

#include <stdio.h>

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

void Image::writeToFile(const std::string& fileName) {
    FILE * file = fopen(fileName.c_str(), "w");
    if (file != nullptr) {
        fprintf(file, "P3\n%d %d\n%d\n", _width, _height, 255);
        for (unsigned int i = 0; i < _width*_height; i++) {
            fprintf(file, "%d %d %d ", _pixels[i].r, _pixels[i].g, _pixels[i].b);
        }
        fclose(file);
    }
}