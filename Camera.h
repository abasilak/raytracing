#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Ray.h"

class Camera {

private:

// Properties
    Vec3  m_origin;
    Vec3  m_lower_left_corner;
    Vec3  m_horizontal;
    Vec3  m_vertical;

// For Defocus blur
    Vec3  m_u;
    Vec3  m_v;
    Vec3  m_w;
    float m_lens_radius;

// For motion blur - shutter open/close times
    float m_time_open;
    float m_time_close;

public:

    explicit Camera() { };
    explicit Camera(const Vec3& origin, 
                    const Vec3& lower_left_corner,
                    const Vec3& horizontal,
                    const Vec3& vertical);
    explicit Camera(const Vec3& origin,
                    const Vec3& lookat,
                    const Vec3& up,
                    float fov, float aspect,
                    float aperture  = 0.0f, float focus_distance = 1.0f,
                    float time_open = 0.0f, float time_close     = 1.0f);
    ~Camera() {};

    Ray GetRay(float s, float t) const;
};
#endif
