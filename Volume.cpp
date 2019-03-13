#include "Volume.h"

#define RT_RAY_STEP 0.0001f

bool
Volume::Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const
{
	hit_record_t _hit_record_1, _hit_record_2;
	if(m_object->Intersect(ray, -std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), _hit_record_1) &&
	   m_object->Intersect(ray,     _hit_record_1.m_t + RT_RAY_STEP, std::numeric_limits<float>::max(), _hit_record_2)
	  ) {

		_hit_record_1.m_t = std::max(_hit_record_1.m_t, t_min);
		_hit_record_2.m_t = std::min(_hit_record_2.m_t, t_max);
		if(_hit_record_1.m_t >= _hit_record_2.m_t) {
			return false;
		}

		float _distance_in_object = (_hit_record_2.m_t - _hit_record_1.m_t)*ray.GetDirection().length();
		float _hit_distance		  = -(1.0f / m_density)*std::log(RANDOM_GEN());
		if(_hit_distance < _distance_in_object) {
			hit_record.m_t        = _hit_record_1.m_t + _hit_distance/ray.GetDirection().length();
			hit_record.m_point    = ray.GetPoint(hit_record.m_t);
			hit_record.m_normal   = Vec3(1.0f,0.0f,0.0f);
			hit_record.m_material = m_material;
			return true;
		}
	}

    return false;
}

bool
Volume::CreateBoundingBox(float t_start, float t_end, AABB& aabb) const
{
    return m_object->CreateBoundingBox(t_start, t_end, aabb);
}
