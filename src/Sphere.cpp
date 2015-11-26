#include "Ray.h"
#include "Sphere.h"
#include <math.h>

Sphere::Sphere(double radius, const Vector3D& center, const Vector3D& surfaceColor, double transparency, double reflection, const Vector3D& emissionCollor)
    : _radius(radius), _center(center), _surfaceColor(surfaceColor), _transparency(transparency), _reflection(reflection), _emissionColor(emissionCollor)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(const Ray& ray, double& t0, double& t1) const
{
    double r2 = pow(_radius, 2);
    Vector3D v = _center - ray.getOrigin();
    double b = v.dot(ray.getDirection());
    double d2 = (b * b) - v.dot(v) + r2;

    if (d2 > r2)
        return false;

    double d = sqrt(r2 - d2);

    t0 = b - d;
    t1 = b + d;

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
