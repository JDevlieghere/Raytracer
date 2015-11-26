#include "Image.h"

#include <algorithm>
#include <fstream>

Image::Image(unsigned int width, unsigned int height) : _width(width), _height(height)
{
    _pixels = new Vector3D[width * height];
}

Image::~Image()
{
    if (_pixels)
    {
        delete _pixels;
        _pixels = nullptr;
    }
}

const Vector3D& Image::getPixel(unsigned int x, unsigned int y) const
{
    return _pixels[getIndex(x, y)];
}

void Image::setPixel(unsigned int x, unsigned int y, const Vector3D& pixel)
{
    _pixels[getIndex(x, y)] = pixel;
}

unsigned int Image::getIndex(unsigned int x, unsigned int y) const
{
    return y * _width + x;
}

unsigned int Image::getWidth() const
{
    return _width;
}

unsigned int Image::getHeight() const
{
    return _height;
}

void Image::writeToFile(const std::string& fileName)
{
    std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << _width << " " << _height << "\n255\n";
    for (unsigned i = 0; i < _width * _height; ++i)
    {
        ofs << static_cast<unsigned char>(std::min(double(1), _pixels[i].getX()) * 255)
            << static_cast<unsigned char>(std::min(double(1), _pixels[i].getY()) * 255)
            << static_cast<unsigned char>(std::min(double(1), _pixels[i].getZ()) * 255);
    }
    ofs.close();
}