#pragma once

#include "Camera.h"
#include "Image.h"
#include "Scene.h"
#include "Vector3D.h"
#include <math.h>

class Sphere;
class Ray;
class Scene;

class Renderer
{
public:
    Renderer(const Camera& camera, Scene& scene, int maxDepth = 5, int samples = 1);

    void render();

private:

    static double Fresnel(const double& theta, const double& level);

    Vector3D trace(const Ray& ray, const int depth) const;
    void intersect(const Ray& ray, const Sphere* sphere, double& t) const;

    Camera _camera;
    Scene _scene;
    int _maxDepth;
    int _samples;

    const Vector3D BACKGROUND_COLOR = Vector3D(1);
    const double EPSILON = 1e-4;

};