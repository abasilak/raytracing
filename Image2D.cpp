#include "Image2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image2D::Image2D(const std::string &name, const std::string &type, int width, int height)
: m_name(name),
  m_width(width),
  m_height(height),
  m_components(3)
{
	if (type == "PPM") {
		m_type = FileType::PPM;
	}
	else if (type == "PNG") {
		m_type = FileType::PNG;
	}
	else if (type == "BMP") {
		m_type = FileType::BMP;
	}
	else if (type == "TGA") {
		m_type = FileType::TGA;
	}
	else if (type == "HDR") {
		m_type = FileType::HDR;
	}
}

bool
Image2D::OpenFile(void)
{
    m_ofstream.open(m_name);

    if(!m_ofstream.is_open()) {
        std::cerr << "\nUnable to open file: " + m_name << std::endl;
        return false;
    }
    return true;
}

unsigned char *
Image2D::LoadFile(const std::string &name)
{
	m_name = name;
	return stbi_load(m_name.c_str(), &m_width, &m_height, &m_components, 0);
}

bool
Image2D::WritePixel2File(Vec3 **colors)
{
	if (m_type == FileType::PPM) {
		if (!OpenFile()) {
			return false;
		}

		m_ofstream << "P3\n";
		m_ofstream << m_width << " " << m_height << "\n";
		m_ofstream << "255\n";

		for (int j = m_height - 1; j >= 0; --j) {
			for (int i = 0; i < m_width; ++i) {

				Vec3 color = colors[i][j];
				int r = int(255.99 * color[0]);
				int g = int(255.99 * color[1]);
				int b = int(255.99 * color[2]);

				m_ofstream << r << " " << g << " " << b << "\n";
			}
		}
		CloseFile();
	} 
	else {
		unsigned char *output_image = FramebufferToArray(colors);
		if (m_type == FileType::PNG) {
			stbi_write_png(m_name.c_str(), m_width, m_height, m_components, output_image, m_width * m_components);
		}
		else if (m_type == FileType::BMP) {
			stbi_write_bmp(m_name.c_str(), m_width, m_height, m_components, output_image);
		}
		else if (m_type == FileType::TGA) {
			stbi_write_tga(m_name.c_str(), m_width, m_height, m_components, output_image);
		}
		else if (m_type == FileType::HDR) {
			//tbi_write_hdr(m_name.c_str(), m_width, m_height, 3, output_image);
		}
	}

	return true;
}

void
Image2D::CloseFile(void)
{
    m_ofstream.close();
}

unsigned char*
Image2D::FramebufferToArray(Vec3 **framebuffer)
{
	int width = static_cast<int>(m_width);
	int height = static_cast<int>(m_height);

	unsigned char *output = new unsigned char[width * height * m_components];
	unsigned char *output_ptr = output;

	for (int j = height - 1; j >= 0; --j)
	{
		unsigned char *temp = new unsigned char[m_components * width];
		unsigned char *temp_ptr = temp;

		for (int i = 0; i < width; ++i)
		{
			int rgb[3];
			rgb[0] = (unsigned char)(255.99 * framebuffer[i][j].x());
			rgb[1] = (unsigned char)(255.99 * framebuffer[i][j].y());
			rgb[2] = (unsigned char)(255.99 * framebuffer[i][j].z());
			std::copy(rgb, rgb + m_components, temp_ptr);
			temp_ptr += m_components;
		}

		std::copy(temp, temp + (width * m_components), output_ptr);
		output_ptr += width * m_components;
		delete[] temp;
	}

	return output;
}