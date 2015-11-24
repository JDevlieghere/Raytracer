#pragma once

#include "Image.h"
#include "Sphere.h"

#include <vector>

class Scene {
public:
    Scene(Image image);

    void setSpheres(const std::vector<Sphere>& spheres);
    const std::vector<Sphere>& getSpheres();

	const Image& getImage() const;
	Image& accessImage();

private:
    std::vector<Sphere> _spheres;
	Image _image;

};