#pragma once

#include "Vector3D.h"

class Ray;

class Sphere {
public:
    Sphere(Vector3D center, double radius);
    ~Sphere();

    const Vector3D& getCenter();
    const double getRadius();

    double intersect(const Ray& ray) const;
private:
    Vector3D _center;
    double _radius;
};