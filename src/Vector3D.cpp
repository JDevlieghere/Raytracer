#include <math.h>
#include "Vector3D.h"

Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) { }

Vector3D::~Vector3D() { }

std::ostream& operator<<(std::ostream& os, const Vector3D& v)
{
    os << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
    return os;
}

Vector3D Vector3D::operator+(const Vector3D& v) const {
    return Vector3D(_x + v.getX(), _y + v.getY(), _z + v.getZ());
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
    return Vector3D(_x - v.getX(), _y - v.getY(), _z - v.getZ());
}

Vector3D Vector3D::operator*(const Vector3D& v) const {
    return Vector3D(_x * v.getX(), _y * v.getY(), _z * v.getZ());
}

Vector3D Vector3D::operator*(double d) const {
    return Vector3D(_x * d, _y * d, _z * d);
}

double Vector3D::dotProduct(const Vector3D &v) {
    return _x * v.getX() + _y * v.getY() + _z * v.getZ();
}

Vector3D& Vector3D::normalize() {
    return *this = *this * (1/sqrt(_x*_x + _y*_y + _z*_z));
}

double Vector3D::getX() const {
    return _x;
}

double Vector3D::getY() const {
    return _y;
}
double Vector3D::getZ() const {
    return _z;
}
