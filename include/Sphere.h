#pragma once

#include "Vector3D.h"

class Ray;

class Sphere
{
public:
    Sphere(double radius,
           const Vector3D& center,
           const Vector3D& surfaceColor = 0,
           double transparency = 0,
           double reflection = 0,
           const Vector3D& emissionCollor = 0);
    ~Sphere();

    const Vector3D& getCenter() const;
    const Vector3D& getSurfaceColor() const;
    const Vector3D& getEmissionColor() const;

    double getRadius() const;
    double getTransparency() const;
    double getReflection() const;

    bool intersect(const Ray& ray, double& t0, double& t1) const;
        
private:

    double _radius;
    Vector3D _center;

    Vector3D _surfaceColor;
    double _transparency;
    double _reflection;
    Vector3D _emissionColor;
};