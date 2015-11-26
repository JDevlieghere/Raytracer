#pragma once

#include "Vector3D.h"

#include <string>

class Image
{
public:
    Image(unsigned int width, unsigned int height);
    ~Image();

    const Vector3D& getPixel(unsigned int x, unsigned int y) const;
    void setPixel(unsigned int x, unsigned int y, const Vector3D& pixel);

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void writeToFile(const std::string& fileName);

private:
    unsigned int getIndex(unsigned int x, unsigned int y) const;
    unsigned int _width;
    unsigned int _height;
    Vector3D* _pixels;
};