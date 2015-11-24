#pragma once

#include "Vector3D.h"

class Ray;

class Sphere {
public:
    Sphere(double radius, Vector3D center);
    ~Sphere();

    const Vector3D& getCenter();
    const double getRadius();

    double intersect(const Ray& ray) const;
private:
    double _radius;
    Vector3D _center;
};