#include "Camera.h"

#include <math.h>

Camera::Camera(double fieldOfView) : _fieldOfView(fieldOfView)
{
}

double Camera::getAngle() const
{
    return tan(3.141592653589793 * 0.5 * _fieldOfView / 180.);
}
