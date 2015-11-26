#include "Renderer.h"

#include "Camera.h"
#include "Scene.h"

#include <algorithm>
#include <limits>
#include <stdlib.h>

Renderer::Renderer(const Camera& camera, Scene& scene, int maxDepth, int samples)
    : _camera(camera), _scene(scene), _maxDepth(maxDepth), _samples(samples)
{
}

void Renderer::render()
{
    unsigned width = _scene.getImage().getWidth();
    unsigned height = _scene.getImage().getHeight();
    double invWidth = 1 / double(width), invHeight = 1 / double(height);
    double aspectRatio = width / double(height);

    for (auto y = 0; y < width; y++)
    {
        for (auto x = 0; x < height; x++)
        {
            double xx = (2 * ((x + 0.5) * invWidth) - 1) * _camera.getAngle() * aspectRatio;
            double yy = (1 - 2 * ((y + 0.5) * invHeight)) * _camera.getAngle();
            Vector3D direction(xx, yy, -1);
            Ray ray(Vector3D(), direction.normalize());
            _scene.accessImage().setPixel(x, y, trace(ray, 0));
        }
    }
}

inline double Renderer::Fresnel(const double& theta, const double& level)
{
    return level + theta * (1 - level);
}

Vector3D Renderer::trace(const Ray& ray, const int depth) const
{
    double t = std::numeric_limits<double>::max();
    const Sphere* sphere = nullptr;
    if (!sphere)
        return BACKGROUND_COLOR;

    Vector3D surfaceColor = 0;
    Vector3D intersection = ray.getOrigin() + ray.getDirection() * t;
    Vector3D intersectionNorm = (intersection - sphere->getCenter()).normalize();

    const bool inside = ray.getDirection().dot(intersectionNorm) > 0;
    if (inside)
    {
        intersectionNorm = -intersectionNorm;
    }

    if ((sphere->getTransparency() > 0 || sphere->getReflection() > 0) && depth < _maxDepth)
    {
        double facingRatio = -ray.getDirection().dot(intersectionNorm);
        double fresnelEffect = Fresnel(facingRatio, 0.1);

        Vector3D refelectionOrigin = intersection + intersectionNorm * EPSILON;
        Vector3D reflectionDirection =
            (ray.getDirection() - intersectionNorm * 2 * ray.getDirection().dot(intersectionNorm)).normalize();
        Ray reflectionRay(refelectionOrigin, reflectionDirection);

        Vector3D reflection = trace(reflectionRay, depth + 1);
        Vector3D refraction;

        if (sphere->getTransparency())
        {
            // TODO: Implement refraction;
        }

        surfaceColor = (reflection * fresnelEffect + refraction * (1 - fresnelEffect) * sphere->getTransparency()) *
                       sphere->getSurfaceColor();
    }
    else
    {
        for (auto i = 0; i < _scene.getSpheres().size(); ++i)
        {
            const Sphere& currentSphere = _scene.getSpheres().at(i);
            if (currentSphere.getEmissionColor().getX() > 0)
            {
                Vector3D transmission(1);
                Vector3D lightDirection = (currentSphere.getCenter() - intersection).normalize();

                for (auto j = 0; j < _scene.getSpheres().size(); ++j)
                {
                    if (i != j)
                    {
                        const Sphere& otherSphere = _scene.getSpheres().at(j);
                        double t0, t1;
                        Ray r(intersection + intersectionNorm * EPSILON, lightDirection);
                        if (otherSphere.intersect(r, t0, t1))
                        {
                            transmission = 0;
                            break;
                        }
                    }
                }
                surfaceColor += sphere->getSurfaceColor() * transmission *
                                std::max(double(0), intersectionNorm.dot(lightDirection)) * currentSphere.getEmissionColor();
            }
        }
    }

    return surfaceColor + sphere->getEmissionColor();
}

void Renderer::intersect(const Ray& ray, const Sphere* sphere, double& t) const
{
    for (auto s : _scene.getSpheres())
    {
        double t0 = std::numeric_limits<double>::max();
        double t1 = std::numeric_limits<double>::max();
        if (s.intersect(ray, t0, t1))
        {
            t0 = t0 < 0 ? t1 : t0;
            if (t0 < t)
            {
                t = t0;
                sphere = &s;
            }
        }
    }
}
