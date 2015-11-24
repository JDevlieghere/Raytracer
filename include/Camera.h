#pragma once

#include "Vector3D.h"
#include "Ray.h"

class Scene;

class Camera {
public:
	Camera(double fieldOfView, Ray gaze);

	Vector3D getHorizontal(Scene& scene);
	Vector3D getVertical(Scene& scene);

private:
	double _fieldOfView;
	Ray _gaze;
};