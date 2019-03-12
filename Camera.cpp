#include "Utils.h"
#include "Camera.h"

Camera::Camera(const Vec3& origin, const Vec3& lower_left_corner,const Vec3& horizontal,const Vec3& vertical)
: m_origin(origin), m_lower_left_corner(lower_left_corner), m_horizontal(horizontal), m_vertical(vertical)
{

}

Camera::Camera(const Vec3& origin, const Vec3& lookat, const Vec3& up, float fov, float aspect, float aperture, float focus_distance, float time_open, float time_close)
: m_origin(origin), m_lens_radius(aperture * 0.5f), m_time_open(time_open), m_time_close(time_close)
{ 
    float _theta       = degrees_to_radians(fov);
    float _half_height = tan(_theta/2.0f);
    float _half_width  = aspect * _half_height;
    
    m_w = unit_vector(origin - lookat);
    m_u = unit_vector(cross(up, m_w));
    m_v = cross(m_w, m_u);
    
    Vec3 _half_horizontal = _half_width  * m_u * focus_distance;
    Vec3 _half_vertical   = _half_height * m_v * focus_distance;

    m_horizontal        = 2.0f * _half_horizontal;
    m_vertical          = 2.0f * _half_vertical;
    m_lower_left_corner = m_origin - _half_horizontal - _half_vertical - m_w * focus_distance;
}

Ray
Camera::GetRay(float s, float t) const
{ 
    Vec3  _rd     = (m_lens_radius > 0.0f) ? m_lens_radius * random_in_unit_disk() : Vec3(0.0f, 0.0f, 0.0f);
    Vec3  _offset = m_u * _rd.x() + m_v * _rd.y();
    Vec3  _origin = m_origin + _offset;
    float _time   = m_time_open + RANDOM()*(m_time_close - m_time_open);

    return Ray(_origin, m_lower_left_corner + s*m_horizontal + t*m_vertical - _origin, _time);
}