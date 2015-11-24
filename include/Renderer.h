#pragma once

#include "Scene.h"
#include "Camera.h"

class Renderer {
public:
    Renderer(Scene scene, Camera camera, int samples = 1);

private:
    Scene _scene;
    Camera _camera;
    int _samples;
};

inline double clamp(double x) {
    return x < 0 ? 0 : x>1 ? 1 : x;
}

inline int toInt(double x) {
    return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
}