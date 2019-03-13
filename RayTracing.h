#ifndef __RAY_TRACING_H__
#define __RAY_TRACING_H__

#include "Ray.h"
#include "Image2D.h"
#include "Camera.h"
#include "ObjectList.h"

void   compute_ray_tracing(int width, int height, int samples, Camera *camera, Object *list, Image2D *image);
Vec3   compute_sample_color(const Ray& ray, Object *list, int depth);
Vec3   compute_background_color(const Ray& ray);
Vec3   compute_gamma_corrected_color(const Vec3& color, float gamma);

#endif 