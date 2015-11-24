#pragma once

#include "Vector3D.h"

class Ray {
public:
    Ray(Vector3D origin, Vector3D direction);
    ~Ray();

    const Vector3D& getOrigin() const;
    const Vector3D& getDirection() const;

private:
    Vector3D _origin;
    Vector3D _direction;
};