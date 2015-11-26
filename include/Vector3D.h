#pragma once

#include <iostream>

class Vector3D
{
public:
    Vector3D();
    Vector3D(double d);
    Vector3D(double x, double y, double z);

    Vector3D operator+(const Vector3D& v) const;
    Vector3D operator-(const Vector3D& v) const;
    Vector3D operator-() const;
    Vector3D operator*(const Vector3D& v) const;
    Vector3D operator*(double d) const;
    Vector3D& operator += (const Vector3D& v);


    double dot(const Vector3D& v) const;
    Vector3D& normalize();

    double getX() const;
    double getY() const;
    double getZ() const;

private:
    double _x;
    double _y;
    double _z;
};

std::ostream& operator<<(std::ostream& os, const Vector3D& v);