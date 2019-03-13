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

// Image
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
    Scene   _scene(500,500,500);
    Object *_objects_list = _scene.Create();

// Ray Tracing
	compute_ray_tracing(_width, _height, _samples, &_camera, _objects_list, _image);

// Clean
    safe_delete(_image);
    safe_delete(_objects_list);

    return 0;
}
