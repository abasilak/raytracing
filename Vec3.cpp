#include "Utils.h"
#include "Vec3.h"

Vec3 
Vec3::ColorBlack()
{ 
    return Vec3(0.0f,0.0f,0.0f);
}

Vec3
operator+(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

Vec3
operator-(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

Vec3
operator*(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

Vec3
operator/(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

Vec3
operator*(float t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

Vec3
operator/(const Vec3& v, float t) {
    return Vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

Vec3
operator*(const Vec3 &v, float t) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

float
dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
}

Vec3
cross(const Vec3 &v1, const Vec3 &v2) {
    return Vec3( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}

Vec3
unit_vector(const Vec3& v)
{
    return v / v.length();
}

Vec3
random_in_unit_disk(void)
{
    Vec3 _point;
    do {
        _point = 2.0f * Vec3(RANDOM(), RANDOM(), RANDOM()) - Vec3(1.0f, 1.0f, 1.0f);

    } while (dot(_point,_point) >= 1.0f);

    return _point;
}

Vec3
random_in_unit_disk_2(void)
{
    Vec3 _point;
    do {
        _point = 2.0f * Vec3(RANDOM(), RANDOM(), 0.0f) - Vec3(1.0f, 1.0f, 0.0f);

    } while (dot(_point,_point) >= 1.0f);

    return _point;
}

Vec3
reflect(const Vec3& vector, const Vec3& normal)
{
    return vector - 2.0f*dot(vector,normal)*normal;
}

bool
refract(const Vec3& vector, const Vec3& normal, float ni_over_nt, Vec3& refracted)
{
    Vec3  _uv           = unit_vector(vector);
    float _dt           = dot(_uv, normal);
    float _discriminant = 1.0f - ni_over_nt*ni_over_nt*(1.0f-_dt*_dt);

    if (_discriminant > 0.0f) {
        refracted = ni_over_nt*(_uv - normal*_dt) - normal*sqrt(_discriminant);
        return true;
    }
    return false;
}