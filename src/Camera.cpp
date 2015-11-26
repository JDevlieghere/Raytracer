#include "Camera.h"
#include "Scene.h"

Camera::Camera(double fieldOfView, Ray gaze) : _fieldOfView(fieldOfView), _gaze(gaze)
{
}

const Ray& Camera::getGaze() const
{
    return _gaze;
}

double Camera::getAngle() const
{
    return tan(3.141592653589793 * 0.5 * _fieldOfView / 180.);
}
