#include "RayTracing.h"
#include "Sphere.h"
#include "Camera.h"
#include "Scene.h"
#include "Image2D.h"
#include "Utils.h"

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
    const std::string _name    = std::string(argv[4]) + "_" + std::string(argv[1]) + "_" + std::string(argv[2]) + "_" + std::string(argv[3]) + std::string(IMAGE_EXT);

    Image2D *_image = new Image2D(_name, _width, _height);
    if(!_image->OpenFile()){
        return 1;
    }
    _image->InitFile();

    srand48(time(NULL));

// Camera
    const Vec3  _origin = Vec3(10.0f,  10.0f, 20.0f);
    const Vec3  _lookat = Vec3( 0.0f,  0.0f,  0.0f);
    const Vec3  _up     = Vec3( 0.0f,  1.0f,  0.0f);
    const float _fov    = 20.0f;
    const float _aspect = static_cast<float>(_width) / static_cast<float>(_height);
    const float _aperture       = 0.1f;
    const float _focus_distance = (_origin - _lookat).length();

    Camera _camera(_origin, _lookat, _up, _fov, _aspect, _aperture, _focus_distance);

// Scene
    Scene  _scene(500,500);

    ObjectList     *_objects_list = _scene.Create();

// Post-Processing
    const float _gamma = 0.5f;

#ifdef EXECUTION_TIME_COMPUTATION
    auto start = high_resolution_clock::now(); 
#endif

    std::cout << "\nRay Tracing Progress" << std::endl;

// For each pixel
    double pr = 0.0;
    for(int j=_height-1; j>=0; --j) {
        for(int i=0; i<_width; ++i) {
            
            Vec3 _color(0.0f,0.0f,0.0f);
            for(int s=0; s<_samples; ++s) {

// Compute pixel sample coords - UV
                float _u = static_cast<float>(i + drand48()) / static_cast<float>(_width );
                float _v = static_cast<float>(j + drand48()) / static_cast<float>(_height);

// Compute ray that pass through each pixel
                Ray  _ray = _camera.GetRay(_u, _v);

// Compute pixel sample color
                _color += compute_sample_color(_ray, _objects_list, 0);
            }
            _color /= static_cast<float>(_samples);

// Gamma Correction
            _color = compute_gamma_corrected_color(_color, _gamma);

// Write pixel color to image file
            _image->WritePixel2File(_color);

            printProgress(pr++/(_width*_height));
        }
    }

#ifdef EXECUTION_TIME_COMPUTATION
    auto stop     = high_resolution_clock::now();

// Subtract stop and start timepoints and cast it to required unit. 
// Predefined units are nanoseconds, microseconds, milliseconds, 
// seconds, minutes, hours. Use duration_cast() function. 
    auto duration = duration_cast<milliseconds>(stop - start); 

// To get the value of duration use the count() 
// member function on the duration object 
    std::cout << "\nImage '" << _name <<"' was successfully generated in " << duration.count() << " ms" << std::endl;
#endif

    _image->CloseFile();
    
    safe_delete(_image);
    
    safe_delete(_objects_list);

    return 0;
}