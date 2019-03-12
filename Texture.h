#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Utils.h"
#include "Vec3.h"

class Texture
{
public:
    virtual ~Texture() {};
    
    virtual Vec3 GetValue(float u, float v, const Vec3& pos) const = 0;
};

class SolidTexture : public Texture
{
private:
    Vec3     m_color;

public:
    explicit SolidTexture() {};
    explicit SolidTexture(Vec3 color) : m_color(color) {};
    ~SolidTexture() {};
    
    virtual Vec3 GetValue(float u, float v, const Vec3& pos) const override { return m_color; }
};

class CheckerTexture : public Texture
{
private:
	Texture *m_odd;
	Texture *m_even;

public:
	explicit CheckerTexture() : m_odd(nullptr), m_even(nullptr)  {};
	explicit CheckerTexture(Texture *odd, Texture *even) : m_odd(odd), m_even(even) { };
	~CheckerTexture() {
		safe_delete(m_odd);
		safe_delete(m_even);
	};

	virtual Vec3 GetValue(float u, float v, const Vec3& pos) const override {
		
		Vec3   _pos   = 10.0f*pos;
		float  _sines = std::sin(_pos.x()) * std::sin(_pos.y()) * std::sin(_pos.z());
		
		return _sines > 0.0f ? m_odd->GetValue(u, v, pos) : m_even->GetValue(u, v, pos);
	}
};

class ImageTexture : public Texture
{
private:
	int				m_width;
	int				m_height;
	unsigned char  *m_data;

public:
	explicit ImageTexture() {};
	explicit ImageTexture(int width, int height, unsigned char *data) : m_width(width), m_height(height), m_data(data) { };
	~ImageTexture() {};

	virtual Vec3 GetValue(float u, float v, const Vec3& pos) const override {
		int   _i		= (int)std::max(0.0f, std::min(m_width  - 1.0f, (u)*m_width));
		int   _j		= (int)std::max(0.0f, std::min(m_height - 1.0f, (1.0f - v)*m_height - 0.001f));

		int	  _i3       = _i * 3;
		int	  _j3_width = _j * 3 * m_width;
		float _r		= int(m_data[_i3 + _j3_width]    ) / 255.0f;
		float _g		= int(m_data[_i3 + _j3_width + 1]) / 255.0f;
		float _b		= int(m_data[_i3 + _j3_width + 2]) / 255.0f;

		return Vec3(_r, _g, _b);
	}
};

#endif 
