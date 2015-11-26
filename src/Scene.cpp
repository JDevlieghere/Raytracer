#include "Scene.h"

Scene::Scene(Image image) : _image(image)
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

const Image& Scene::getImage() const
{
    return _image;
}

Image& Scene::accessImage()
{
    return _image;
}