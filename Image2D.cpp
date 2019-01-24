#include "Image2D.h"

Image2D::Image2D(const std::string &name, int width, int height)
: m_name(name),
  m_width(width),
  m_height(height)
{

}

bool
Image2D::OpenFile(void)
{
    m_image.open(m_name);

    if(!m_image.is_open()) {
        std::cerr << "\nUnable to open file: " << m_name << std::endl;
        return false;
    }
    return true;
}

void
Image2D::InitFile(void)
{
    m_image << "P3\n";  
    m_image << m_width << " " << m_height << "\n";
    m_image << "255\n";
}

void
Image2D::WritePixel2File(Vec3 **colors)
{
    for(int j=m_height-1; j>=0; --j) {
        for(int i=0; i<m_width; ++i) {

            Vec3 color = colors[i][j];
            int r = int (255.99 * color[0]);
            int g = int (255.99 * color[1]);
            int b = int (255.99 * color[2]);

            m_image << r << " " << g << " " << b << "\n";
        }
    }
}

void
Image2D::CloseFile(void)
{
    m_image.close();
}