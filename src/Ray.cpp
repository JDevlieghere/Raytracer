#include "Ray.h"

Ray::Ray(Vector3D origin, Vector3D direction) : _origin(origin), _direction(direction) { }

Ray::~Ray() { }

const Vector3D& Ray::getOrigin() const {
    return _origin;
}

const Vector3D& Ray::getDirection() const {
    return _direction;
}