#ifndef __VEC3_H__
#define __VEC3_H__

#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

class Vec3 {

public:
    float e[3];

public:

    explicit Vec3() {}
    explicit Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    Vec3(const Vec3 &v) { e[0] = v[0]; e[1] = v[1]; e[2] = v[2]; }
    ~Vec3() {}

    static Vec3 ColorBlack();

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }
    
    inline const Vec3&  operator+()       const { return *this; }
    inline       Vec3   operator-()       const { return Vec3(-e[0], -e[1], -e[2]); }
    inline float        operator[](int i) const { return e[i]; }
    inline float&       operator[](int i)       { return e[i]; };
    
    inline Vec3&        operator+=(const Vec3 &v) { e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2]; return *this;}
    inline Vec3&        operator-=(const Vec3 &v) { e[0] -= v.e[0]; e[1] -= v.e[1]; e[2] -= v.e[2]; return *this;}
    inline Vec3&        operator*=(const Vec3 &v) { e[0] *= v.e[0]; e[1] *= v.e[1]; e[2] *= v.e[2]; return *this;}
    inline Vec3&        operator/=(const Vec3 &v) { e[0] /= v.e[0]; e[1] /= v.e[1]; e[2] /= v.e[2]; return *this;}
    inline Vec3&        operator+=(const float t) { e[0] +=      t; e[1] +=      t; e[2] +=      t; return *this;}
    inline Vec3&        operator-=(const float t) { e[0] -=      t; e[1] -=      t; e[2] -=      t; return *this;}
    inline Vec3&        operator*=(const float t) { e[0] *=      t; e[1] *=      t; e[2] *=      t; return *this;}
    inline Vec3&        operator/=(const float t) { e[0] /=      t; e[1] /=      t; e[2] /=      t; return *this;}
   
    inline float squared_length()   const   { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    inline float length()           const   { return sqrtf(squared_length()); }
    inline void  make_unit_vector()         { *this /= length(); }
};

float dot  (const Vec3 &v1, const Vec3 &v2);
Vec3  cross(const Vec3 &v1, const Vec3 &v2);
Vec3  unit_vector(const Vec3& v);
Vec3  random_in_unit_disk(void);
Vec3  random_in_unit_disk_2(void);
Vec3  reflect(const Vec3& vector, const Vec3& normal);
bool  refract(const Vec3& vector, const Vec3& normal, float ni_over_nt, Vec3& refracted);

Vec3 operator*(const Vec3 &v, float t);
Vec3 operator*(float t      , const Vec3 &v);
Vec3 operator/(const Vec3 &v, float t);
Vec3 operator+(const Vec3 &v1, const Vec3 &v2);
Vec3 operator-(const Vec3 &v1, const Vec3 &v2);
Vec3 operator*(const Vec3 &v1, const Vec3 &v2);
Vec3 operator/(const Vec3 &v1, const Vec3 &v2);

#endif
