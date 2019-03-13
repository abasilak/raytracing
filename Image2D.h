#ifndef __IMAGE2D_H__
#define __IMAGE2D_H__

#include <string>
#include <iostream>
#include <fstream>
#include "Vec3.h"

class Image2D {

private:
	enum FileType { PPM, PNG, BMP, TGA, HDR };

    std::string     m_name;
    int             m_width;
    int             m_height;
	int				m_components;
    std::ofstream   m_ofstream;
	FileType		m_type;

public:
    explicit Image2D() {};
    explicit Image2D(const std::string &name, const std::string &type, int width, int m_height);
    ~Image2D() {};

    bool			OpenFile(void);
	unsigned char  *LoadFile(const std::string &name);
	bool			WritePixel2File(Vec3 **colors);
    void			CloseFile(void);
	unsigned char*	FramebufferToArray(Vec3 **framebuffer);

	inline int		GetWidth(void)		 const { return m_width;  }
	inline int		GetHeight(void)		 const { return m_height; }
	inline int		GetComponents(void)  const { return m_components;   }
};


#endif
