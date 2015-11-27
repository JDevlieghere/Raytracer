#include "Image.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

Image::Image(unsigned width, unsigned height) : _width(width), _height(height)
{
    _pixels = std::vector<Vector3D>(_width * _height);
}

Image::~Image()
{
}

void Image::setPixel(unsigned i, const Vector3D& pixel)
{
    _pixels[i] = pixel;
}

void Image::writeToFile(const std::string& fileName) const
{
    std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
    ofs << "P6\n" << _width << " " << _height << "\n255\n";
    for (unsigned i = 0; i < _width * _height; ++i)
    {
        ofs << static_cast<unsigned char>(std::min(double(1), _pixels[i].getX()) * 255)
            << static_cast<unsigned char>(std::min(double(1), _pixels[i].getY()) * 255)
            << static_cast<unsigned char>(std::min(double(1), _pixels[i].getZ()) * 255);
    }
    ofs.close();
}
