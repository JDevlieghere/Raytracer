#include "Renderer.h"

#include "Camera.h"
#include "Scene.h"

#include <algorithm>
#include <iostream>
#include <limits>

Renderer::Renderer(const Camera& camera, Scene& scene, int maxDepth, int samples)
    : _camera(camera), _scene(scene), _image(scene.getWidth(), scene.getHeight()), _maxDepth(maxDepth), _samples(samples)
{
}

void Renderer::render()
{
    double invWidth = 1 / double(_scene.getWidth());
    double invHeight = 1 / double(_scene.getHeight());
    double aspectRatio = _scene.getWidth() / double(_scene.getHeight());
    unsigned i = 0;
    for (auto y = 0; y < _scene.getHeight(); y++)
    {
        for (auto x = 0; x < _scene.getWidth(); x++, i++)
        {
            double xx = (2 * ((x + 0.5) * invWidth) - 1) * _camera.getAngle() * aspectRatio;
            double yy = (1 - 2 * ((y + 0.5) * invHeight)) * _camera.getAngle();
            Vector3D direction(xx, yy, -1);
            Ray ray(Vector3D(0), direction.normalize());
            _image.setPixel(i, trace(ray, 0));
        }
    }
}

const Image& Renderer::getImage() const
{
    return _image;
}

inline double Renderer::Fresnel(const double& theta, const double& level)
{
    return level + theta * (1 - level);
}

Vector3D Renderer::trace(const Ray& ray, const int depth) const
{
    double t = std::numeric_limits<double>::max();
    Sphere sphere;
    const bool hasIntersection = intersect(ray, sphere, t);

    if (!hasIntersection)
    {
        return BACKGROUND_COLOR;
    }

    Vector3D surfaceColor = 0;
    Vector3D intersection = ray.getOrigin() + ray.getDirection() * t;
    Vector3D intersectionNorm = (intersection - sphere.getCenter()).normalize();

    const bool inside = ray.getDirection().dot(intersectionNorm) > 0;
    if (inside)
    {
        intersectionNorm = -intersectionNorm;
    }

    if ((sphere.getTransparency() > 0 || sphere.getReflection() > 0) && depth < _maxDepth)
    {
        double facingRatio = -ray.getDirection().dot(intersectionNorm);
        double fresnelEffect = Fresnel(facingRatio, 0.1);

        Vector3D refelectionOrigin = intersection + intersectionNorm * EPSILON;
        Vector3D reflectionDirection = ray.getDirection() - intersectionNorm * 2 * ray.getDirection().dot(intersectionNorm);
        Ray reflectionRay(refelectionOrigin, reflectionDirection.normalize());

        Vector3D reflection = trace(reflectionRay, depth + 1);
        Vector3D refraction = 0;

        if (sphere.getTransparency())
        {
            double ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
            double cosi = -intersectionNorm.dot(ray.getDirection());
            double k = 1 - eta * eta * (1 - cosi * cosi);
            Vector3D refractionOrigin = intersection - intersectionNorm * EPSILON;
            Vector3D refractionDirection = ray.getDirection() * eta + intersectionNorm * (eta * cosi - sqrt(k));
            refractionDirection.normalize();
            Ray refractionRay(refractionOrigin, refractionDirection);
            refraction = trace(refractionRay, depth + 1);
        }

        surfaceColor = (reflection * fresnelEffect + refraction * (1 - fresnelEffect) * sphere.getTransparency()) *
                       sphere.getSurfaceColor();
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
                surfaceColor += sphere.getSurfaceColor() * transmission *
                                std::max(double(0), intersectionNorm.dot(lightDirection)) * currentSphere.getEmissionColor();
            }
        }
    }
    return surfaceColor + sphere.getEmissionColor();
}

bool Renderer::intersect(const Ray& ray, Sphere& sphere, double& t) const
{
    bool hasIntersection = false;
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
                sphere = s;
                hasIntersection = true;
            }
        }
    }
    return hasIntersection;
}
