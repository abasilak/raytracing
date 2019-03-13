#include "Utils.h"
#include "RayTracing.h"

#define PPE_GAMMA              0.5f
#define RT_MAX_DEPTH           50
#define RT_MIN_INTERSECTION_T  0.001f

void
compute_ray_tracing(int width, int height, int samples, Camera *camera, Object *list, Image2D *image)
{
	std::cout << "\nRay Tracing Progress" << std::endl;

#ifdef EXECUTION_TIME_COMPUTATION
	auto start = high_resolution_clock::now();
#endif

	Vec3 **_colors = new Vec3 *[width];
	for (int i = 0; i < width; ++i) {
		_colors[i] = new Vec3[height];
	}

	float _progress_i	  = 0.0f;
	float _progress_total = static_cast<float>(width*height);
	
#ifdef _OPENMP
#ifdef _WIN32
#pragma omp parallel for
#else
#pragma omp parallel for collapse(2)
#endif
#endif
	// For each pixel (in parallel)
	for (int j = height - 1; j >= 0; --j) {
		for (int i = 0; i < width; ++i) {

			_colors[i][j] = Vec3(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < samples; ++s) {

				// Compute pixel sample coords - UV
				float _u = static_cast<float>(i + RANDOM_GEN()) / static_cast<float>(width);
				float _v = static_cast<float>(j + RANDOM_GEN()) / static_cast<float>(height);

				// Compute ray that pass through each pixel
				Ray _ray = camera->GetRay(_u, _v);

				// Compute pixel sample color
				_colors[i][j] += compute_sample_color(_ray, list, 0);
			}
			// Compute sample-averaged pixel color
			_colors[i][j] /= static_cast<float>(samples);

			// Gamma Correction
			_colors[i][j] = compute_gamma_corrected_color(_colors[i][j], PPE_GAMMA);

			printProgress(++_progress_i / _progress_total);
		}
	}

#ifdef EXECUTION_TIME_COMPUTATION
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	std::cout << "\nImage was successfully generated in " << duration.count() << " ms" << std::endl;
#endif
	
	image->WritePixel2File(_colors);

	for (int i = 0; i < width; ++i) {
		safe_array_delete(_colors[i]);
	}
	safe_array_delete(_colors);
}

Vec3
compute_gamma_corrected_color(const Vec3& color, float gamma)
{
    return Vec3(powf(color[0], gamma), powf(color[1], gamma), powf(color[2], gamma));
}

Vec3
compute_background_color(const Ray& ray)
{
    // Background color
    const Vec3  _a(0.0f,0.0f,0.0f);
    const Vec3  _b(0.15f,0.15f,0.15f);

    const Vec3  _unit_dir = unit_vector(ray.GetDirection());  
    const float _t = 0.5f * (_unit_dir.y() + 1.0f); // [-1,1] -> [0,1]

    return lerp(_a, _b, _t);
}

Vec3
compute_sample_color(const Ray& ray, Object *list, int depth)
{
    hit_record_t _hit_record;
    if(list->Intersect(ray, RT_MIN_INTERSECTION_T, std::numeric_limits<float>::max(), _hit_record)) {
        Ray  _scattered;
        Vec3 _attenuation;
		Vec3 _emitted = _hit_record.m_material->Emitted(_hit_record.m_point, _hit_record.m_u, _hit_record.m_v);
        if (depth < RT_MAX_DEPTH && _hit_record.m_material->Scatter(ray, _hit_record, _attenuation, _scattered)) {
            return _emitted + _attenuation * compute_sample_color(_scattered, list, depth+1);
        }
        else {
            return _emitted;
        }
    }

    return compute_background_color(ray);
}