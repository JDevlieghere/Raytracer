#include "Ray.h"
#include "Sphere.h"
#include <iostream>
#include <math.h>

Sphere::Sphere(const Vector3D& center, double radius, const Vector3D& surfaceColor, double transparency, double reflection, const Vector3D& emissionCollor)
    : _center(center), _radius(radius), _surfaceColor(surfaceColor), _transparency(transparency), _reflection(reflection), _emissionColor(emissionCollor)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(const Ray& ray, double& t0, double& t1) const
{
    Vector3D l = _center - ray.getOrigin();
    double tca = l.dot(ray.getDirection());
    if (tca < 0)
        return false;
    double d2 = l.dot(l) - tca * tca;
    double r2 = _radius * _radius;
    if (d2 > r2)
        return false;
    float thc = sqrt(r2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;
    return true;
}

double Sphere::getRadius() const
{
    return _radius;
}

double Sphere::getTransparency() const
{
    return _transparency;
}

double Sphere::getReflection() const
{
    return _reflection;
}

const Vector3D& Sphere::getCenter() const
{
    return _center;
}

const Vector3D& Sphere::getSurfaceColor() const
{
    return _surfaceColor;
}

const Vector3D& Sphere::getEmissionColor() const
{
    return _emissionColor;
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere)
{
    os << "[" << sphere._center << "," << sphere._radius << ", " << sphere._surfaceColor << "]";
    return os;
}
