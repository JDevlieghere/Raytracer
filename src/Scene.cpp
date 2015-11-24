#include "Scene.h"

Scene::Scene(int width, int heigth) : _width(width), _height(heigth) { }

int Scene::getWidth() {
    return _width;
}

int Scene::getHeight() {
    return _height;
}

void Scene::setSpheres(const std::vector<Sphere*>& spheres)
{
	_spheres = spheres;
}

const std::vector<Sphere*>& Scene::getSpheres()
{
	return _spheres;
}