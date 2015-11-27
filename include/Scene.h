#pragma once

#include "Image.h"
#include "Sphere.h"

#include <vector>

class Scene
{
public:
    Scene(unsigned width, unsigned height);

    void setSpheres(const std::vector<Sphere>& spheres);
    const std::vector<Sphere>& getSpheres() const;
    std::vector<Sphere>& accessSpheres();

    unsigned getWidth() const;
    unsigned getHeight() const;

private:
    std::vector<Sphere> _spheres;
    unsigned _width;
    unsigned _height;
};