#ifndef __RAY_TRACING_H__
#define __RAY_TRACING_H__

#include "Ray.h"
#include "ObjectList.h"

Vec3 compute_sample_color(const Ray& ray, ObjectList *list, int depth);
Vec3 compute_background_color(const Ray& ray);
Vec3 compute_gamma_corrected_color(const Vec3& _color, float _gamma);

#endif 