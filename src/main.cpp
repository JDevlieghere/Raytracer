#include <iostream>

#include "Image.h"
#include "Renderer.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vector3D.h"

#include <vector>

int main(int argc, char* argv[])
{
    std::vector<Sphere> spheres;
    // position, radius, surface color, reflectivity, transparency, emission color
    spheres.push_back(Sphere(Vector3D(0.0, -10004, -20), 10000, Vector3D(0.20, 0.20, 0.20), 0, 0.0));
    spheres.push_back(Sphere(Vector3D(0.0, 0, -20), 4, Vector3D(1.00, 0.32, 0.36), 1, 0.5));
    spheres.push_back(Sphere(Vector3D(5.0, -1, -15), 2, Vector3D(0.90, 0.76, 0.46), 1, 0.0));
    spheres.push_back(Sphere(Vector3D(5.0, 0, -25), 3, Vector3D(0.65, 0.77, 0.97), 1, 0.0));
    spheres.push_back(Sphere(Vector3D(-5.5, 0, -15), 3, Vector3D(0.90, 0.90, 0.90), 1, 0.0));
    // light
    spheres.push_back(Sphere(Vector3D(0.0, 20, -30), 3, Vector3D(0.00, 0.00, 0.00), 0, 0.0, Vector3D(3)));
    Scene scene(640, 480);
    scene.setSpheres(spheres);

    Camera camera(50);

    Renderer renderer(camera, scene, 20);
    renderer.render();

    const Image& image = renderer.getImage();
    image.writeToFile("render.ppm");
}
