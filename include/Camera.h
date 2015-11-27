#pragma once

#include "Ray.h"
#include "Vector3D.h"

class Scene;

class Camera
{
public:
    Camera(double fieldOfView);

    double getAngle() const;

private:
    double _fieldOfView;
};