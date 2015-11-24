#include "Camera.h"
#include "Scene.h"

Camera::Camera(double fieldOfView, Ray gaze) : _fieldOfView(fieldOfView), _gaze(gaze) {}

Vector3D Camera::getHorizontal(Scene & scene)
{
	return Vector3D((scene.getImage().getWidth() * _fieldOfView)/scene.getImage().getHeight());
}

Vector3D Camera::getVertical(Scene & scene)
{
	return Vector3D(0, (scene.getImage().getHeight() * _fieldOfView) / scene.getImage().getHeight());
}
