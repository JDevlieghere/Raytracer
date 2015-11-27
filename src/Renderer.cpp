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

const Vector3D& Renderer::renderDiffuse(const Sphere& sphere, const Ray& intersection) const
{
    Vector3D surfaceColor;
    for (auto i = 0; i < _scene.getSpheres().size(); ++i)
    {
        const Sphere& currentSphere = _scene.getSpheres().at(i);
        if (currentSphere.getEmissionColor().getX() > 0)
        {
            Vector3D transmission(1);
            Vector3D lightDirection = (currentSphere.getCenter() - intersection.getOrigin()).normalize();

            for (auto j = 0; j < _scene.getSpheres().size(); ++j)
            {
                if (i != j)
                {
                    const Sphere& otherSphere = _scene.getSpheres().at(j);
                    double t0, t1;
                    Ray r(intersection.getOrigin() + intersection.getDirection() * EPSILON, lightDirection);
                    if (otherSphere.intersect(r, t0, t1))
                    {
                        transmission = 0;
                        break;
                    }
                }
            }
            surfaceColor += sphere.getSurfaceColor() * transmission *
                            std::max(double(0), intersection.getDirection().dot(lightDirection)) *
                            currentSphere.getEmissionColor();
        }
    }
    return surfaceColor;
}

const Vector3D& Renderer::renderReflection(const Ray& intersection, const Ray& ray, const int depth) const
{
    Vector3D refelectionOrigin = intersection.getOrigin() + intersection.getDirection() * EPSILON;
    Vector3D reflectionDirection =
        ray.getDirection() - intersection.getDirection() * 2 * ray.getDirection().dot(intersection.getDirection());

    Ray reflectionRay(refelectionOrigin, reflectionDirection.normalize());

    return trace(reflectionRay, depth + 1);
}

const Vector3D& Renderer::renderRefraction(const Sphere& sphere, const Ray& intersection, const Ray& ray, const int depth, const bool inside) const
{
    Vector3D refraction;
    if (sphere.getTransparency())
    {
        double ior = 1.1, eta = (inside) ? ior : 1 / ior;
        double cosi = -intersection.getDirection().dot(ray.getDirection());
        double k = 1 - eta * eta * (1 - cosi * cosi);

        Vector3D refractionOrigin = intersection.getOrigin() - intersection.getDirection() * EPSILON;
        Vector3D refractionDirection = ray.getDirection() * eta + intersection.getDirection() * (eta * cosi - sqrt(k));

        Ray refractionRay(refractionOrigin, refractionDirection.normalize());

        refraction = trace(refractionRay, depth + 1);
    }
    return refraction;
}

const Vector3D&
    Renderer::renderSpecular(const Sphere& sphere, const Ray& intersection, const Ray& ray, const int depth, const bool inside) const
{
    Vector3D surfaceColor;

    double angle = -ray.getDirection().dot(intersection.getDirection());
    double fresnelEffect = Fresnel(angle, 0.1);

    Vector3D reflection = renderReflection(intersection, ray, depth);
    Vector3D refraction = renderRefraction(sphere, intersection, ray, depth, inside);

    surfaceColor = (reflection * fresnelEffect + refraction * (1 - fresnelEffect) * sphere.getTransparency()) *
                   sphere.getSurfaceColor();
    return surfaceColor;
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

    Vector3D intersectionOrigin = ray.getOrigin() + ray.getDirection() * t;
    Vector3D intersectionDirection = (intersectionOrigin - sphere.getCenter()).normalize();

    const bool inside = ray.getDirection().dot(intersectionDirection) > 0;
    if (inside)
    {
        intersectionDirection = -intersectionDirection;
    }

    Ray intersection(intersectionOrigin, intersectionDirection);

    Vector3D surfaceColor;
    if ((sphere.getTransparency() > 0 || sphere.getReflection() > 0) && depth < _maxDepth)
    {
        surfaceColor = renderSpecular(sphere, intersection, ray, depth, inside);
    }
    else
    {
        surfaceColor = renderDiffuse(sphere, intersection);
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
