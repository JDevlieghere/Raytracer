#include <math.h>
#include "sphere.h"
#include "ray.h"

Sphere::Sphere(double radius, Vector3D center) : _radius(radius), _center(center){ }

Sphere::~Sphere() { }

double Sphere::intersect(const Ray& ray) const {
    Vector3D v = _center - ray.getOrigin();
    double b = v.dotProduct(ray.getDirection());
    double det = (b*b) - v.dotProduct(v) + (_radius * _radius);
    if (det < 0) {
        return 0;
    }
    return b - sqrt(det);
}

const double Sphere::getRadius() {
    return _radius;
}

const Vector3D& Sphere::getCenter() {
	return _center;
}
