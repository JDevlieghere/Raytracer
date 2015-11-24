#pragma once

#include <iostream>

class Vector3D {
public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);
    ~Vector3D();

    Vector3D operator + (const Vector3D& v) const;
    Vector3D operator - (const Vector3D& v) const;
    Vector3D operator * (const Vector3D& v) const;
    Vector3D operator * (double d) const;

    double dotProduct(const Vector3D& v);
    Vector3D& normalize();

    double getX() const;
    double getY() const;
    double getZ() const;

private:
    double _x;
    double _y;
    double _z;
};

std::ostream& operator<<(std::ostream& os, const Vector3D & v);