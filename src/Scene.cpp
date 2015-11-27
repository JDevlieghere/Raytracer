#include "Scene.h"

Scene::Scene(unsigned width, unsigned height) : _width(width), _height(height)
{
}

void Scene::setSpheres(const std::vector<Sphere>& spheres)
{
    _spheres = spheres;
}

const std::vector<Sphere>& Scene::getSpheres() const
{
    return _spheres;
}

std::vector<Sphere>& Scene::accessSpheres()
{
    return _spheres;
}

unsigned Scene::getWidth() const
{
    return _width;
}

unsigned Scene::getHeight() const
{
    return _height;
}
