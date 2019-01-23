#ifndef __IMAGE2D_H__
#define __IMAGE2D_H__

#include <iostream>
#include <fstream>
#include "Vec3.h"

#define IMAGE_EXT  ".ppm"

class Image2D {

private:
    std::string     m_name;
    int             m_width;
    int             m_height;
    std::ofstream   m_image;

public:
    explicit Image2D(void) {};
    explicit Image2D(const std::string &name, int width, int m_height);
    ~Image2D() {};

    bool     OpenFile(void);
    void     InitFile(void);
    void     WritePixel2File(const Vec3& color);
    void     CloseFile(void);
};


#endif
