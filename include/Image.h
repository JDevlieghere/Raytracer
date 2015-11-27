#pragma once

#include "Vector3D.h"

#include <string>
#include <vector>

class Image
{
public:
    Image(unsigned width, unsigned height);
    ~Image();
    void setPixel(unsigned i, const Vector3D& pixel);
    void writeToFile(const std::string& fileName) const;

private:
    unsigned getIndex(unsigned int x, unsigned int y) const;
    unsigned _width;
    unsigned _height;
    std::vector<Vector3D> _pixels;
};
