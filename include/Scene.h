#pragma once

#include <vector>

class Sphere;

class Scene {
public:
    Scene(int width, int heigth);

    void setSpheres(const std::vector<Sphere*>& spheres);
    const std::vector<Sphere*>& getSpheres();

    int getWidth();
    int getHeight();

private:
    std::vector<Sphere*> _spheres;
    int _width;
    int _height;

};