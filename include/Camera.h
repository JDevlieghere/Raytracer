#pragma once

#include "Ray.h"
#include "Vector3D.h"

class Scene;

class Camera
{
public:
    Camera(double fieldOfView, Ray gaze);

    const Ray& Camera::getGaze() const;

    double getAngle() const;

private:
    double _fieldOfView;
    Ray _gaze;
};