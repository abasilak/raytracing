#include "Utils.h"
#include "RayTracing.h"
#include "Sphere.h"
#include "Volume.h"
#include "Camera.h"
#include "Scene.h"
#include "Image2D.h"

int main (int argc, char *argv[])
{
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " width height samples filename\n";
        return 1;
    }

// Generated Image
    const int         _width   = std::stoi(argv[1]);
    const int         _height  = std::stoi(argv[2]);
    const int         _samples = std::stoi(argv[3]);
	const std::string _type    = std::string(argv[5]);
    const std::string _name    = std::string(argv[4]) + "_" + std::string(argv[1]) + "_" + std::string(argv[2]) + "_" + std::string(argv[3]) + "." + _type;
	Image2D		     *_image   = new Image2D(_name, _type, _width, _height);

#ifdef RANDOM_SCENE
	INIT_RANDOM_GEN();
#endif

// Camera
    const Vec3  _origin         = Vec3(13.0f,  4.0f,  4.0f);
    const Vec3  _lookat         = Vec3( 0.0f,  0.0f,  0.0f);
    const Vec3  _up             = Vec3( 0.0f,  1.0f,  0.0f);
    const float _fov            = 20.0f;
    const float _aspect         = static_cast<float>(_width) / static_cast<float>(_height);
    const float _aperture       = 0.0f;
    const float _focus_distance = (_origin - _lookat).length();
    const float _shutter_open   = 0.0f;;
    const float _shutter_close  = 1.0f;;

    Camera _camera(_origin, _lookat, _up, _fov, _aspect, _aperture, _focus_distance, _shutter_open, _shutter_close);

// Scene
    Scene  _scene(500,500,500);
    Object *_objects_list = _scene.Create();

// Post-Processing
    const float _gamma = 0.5f;

    std::cout << "\nRay Tracing Progress" << std::endl;

#ifdef EXECUTION_TIME_COMPUTATION
    auto start = high_resolution_clock::now(); 
#endif

/////////////////////////
// Perform Ray Tracing //
/////////////////////////

// Initialization
    float _progress_i     = 0.0f;
    float _progress_total = static_cast<float>(_width*_height);

    Vec3 **_colors = new Vec3 *[_width];
    for(int i=0; i<_width; ++i) {
        _colors[i] = new Vec3[_height];
    }

#ifdef _OPENMP
#ifdef _WIN32
#pragma omp parallel for
#else
#pragma omp parallel for collapse(2)
#endif
#endif
// For each pixel (in parallel)
    for(int j=_height-1; j>=0; --j) {
        for(int i=0; i<_width; ++i) {
            
            _colors[i][j] = Vec3(0.0f,0.0f,0.0f);
            for(int s=0; s<_samples; ++s) {

// Compute pixel sample coords - UV
                float _u = static_cast<float>(i + RANDOM_GEN()) / static_cast<float>(_width );
                float _v = static_cast<float>(j + RANDOM_GEN()) / static_cast<float>(_height);

// Compute ray that pass through each pixel
                Ray  _ray = _camera.GetRay(_u, _v);

// Compute pixel sample color
                _colors[i][j] += compute_sample_color(_ray, _objects_list, 0);
            }
// Compute sample-averaged pixel color
            _colors[i][j] /= static_cast<float>(_samples);

// Gamma Correction
            _colors[i][j] = compute_gamma_corrected_color(_colors[i][j], _gamma);

            printProgress(++_progress_i/_progress_total);
        }
    }

// Write pixel colors to image file
    _image->WritePixel2File(_colors);

#ifdef EXECUTION_TIME_COMPUTATION
    auto stop     = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 

    std::cout << "\nImage '" << _name <<"' was successfully generated in " << duration.count() << " ms" << std::endl;
#endif
   
    safe_delete(_image);
    safe_delete(_objects_list);

    for(int i=0; i<_width; ++i) {
        safe_array_delete(_colors[i]);
    }
    safe_array_delete(_colors);

    return 0;
}
