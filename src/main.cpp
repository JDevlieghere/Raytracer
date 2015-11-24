#include <iostream>

#include "Vector3D.h"
#include "Sphere.h"
#include "Scene.h"
#include "Ray.h"
#include "Image.h"

#include <vector>

int main(int argc, char *argv[]) {

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(1e5, Vector3D(1e5 + 1, 40.8, 81.6)));
    spheres.push_back(Sphere(1e5, Vector3D(-1e5 + 99, 40.8, 81.6)));
    spheres.push_back(Sphere(1e5, Vector3D(50, 40.8, 1e5)));
    spheres.push_back(Sphere(1e5, Vector3D(50, 40.8, -1e5 + 170)));
    spheres.push_back(Sphere(1e5, Vector3D(50, 1e5, 81.6)));
    spheres.push_back(Sphere(1e5, Vector3D(50, -1e5 + 81.6, 81.6)));
    spheres.push_back(Sphere(16.5, Vector3D(27, 16.5, 47)));
    spheres.push_back(Sphere(16.5, Vector3D(73, 16.5, 78)));
    spheres.push_back(Sphere(600, Vector3D(50, 681.6 - .27, 81.6)));

    Image image(512, 384);
    Scene scene(image);
    scene.setSpheres(spheres);

    Vector3D cameraOrigin(50, 52, 295.6);
    Vector3D cameraDirection(0, -0.042612, -1);
    Ray camera(cameraOrigin, cameraDirection.normalize());


}
