/*
 * Image2d.h
 *
 *  Created on: Mar 4, 2009
 *      Author: gix
 */

#ifndef IMAGE2D_H_
#define IMAGE2D_H_

#include <vector>
#include <algorithm>


namespace ggl
{

// Don't use Canvas, use Image2d instead.
template<typename T>
class Canvas
{
public:
	virtual void resize(size_t x, size_t y) = 0;

	virtual const size_t & getX()const = 0;
	virtual const size_t & getY()const = 0;

	virtual void putPixel(const int & x, const int & y, const T & pixel) = 0;
	virtual const T & getPixel(const int & x, const int & y)const = 0;
	virtual void clear(const float& value = 0) = 0;
	virtual void clear(const T& value) = 0;

	const size_t& width()const {return getX();}
	const size_t& height()const {return getY();}

	virtual void line(int x0, int y0, int x1, int y1, const T& color);
	virtual void hLine(int x0, int y, int x1, const T& color);
};

template<typename T>
class Image2d : public Canvas<T>
{
public:
	Image2d(size_t x = 0, size_t y = 0);

	void resize(size_t x, size_t y);

	const size_t & getX()const {return _x;}
	const size_t & getY()const {return _y;}

	const size_t& width()const {return getX();}
	const size_t& height()const {return getY();}

	void putPixel(const int & x, const int & y, const T & pixel);
	const T & getPixel(const int & x, const int & y)const {return _array[y*_x + x];}

	void clear(const float& value = 0) {for(size_t i = 0; i < _array.size(); ++i) _array[i].clear(value);}
	void clear(const T& value) {for(size_t i = 0; i < _array.size(); ++i) _array[i]=value;}

private:
	std::vector<T> _array;
	size_t _x, _y;
};

template <typename T>
void Image2d<T>::putPixel(const int & x, const int & y, const T & pixel)
{
	// TODO: this should be using sane copy constructors and allow for copying parents <-> children pixel types
	if( (x < 0) || (y < 0) || (x >= static_cast<int>(width())) || (y >= static_cast<int>(height())))
		return;

	_array[y*_x + x] = pixel;
}

template <typename T>
void Canvas<T>::hLine(int x0, int y, int x1, const T& color)
{
	if(x0 > x1)
		return hLine(x1, y, x0, color);

	for(int i = 0; i < x1 - x0; ++i)
		putPixel(x0 + i, y, color);
}

template <typename T>
void Canvas<T>::line(int x0, int y0, int x1, int y1, const T& color)
{
	/*
	 * bresenham's line algorithm directly copied from wikipedia
	 * FIXME: could be possibly made a bit faster...especially, when boundary checking is not necessary
	 *
	 */

	int Dx = x1 - x0;
	int Dy = y1 - y0;
	int steep = (abs(Dy) >= abs(Dx));
	if (steep) {
		std::swap(x0, y0);	// TODO: maybe custom xored swap could be faster?
	   std::swap(x1, y1);
	   // recompute Dx, Dy after swap
	   Dx = x1 - x0;
	   Dy = y1 - y0;
	}
	int xstep = 1;
	if (Dx < 0) {
		xstep = -1;
	   Dx = -Dx;
	}
	int ystep = 1;
	if (Dy < 0) {
		ystep = -1;
		Dy = -Dy;
	}
	int TwoDy = 2*Dy;
	int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
	int E = TwoDy - Dx; //2*Dy - Dx
	int y = y0;
	int xDraw, yDraw;
	for (int x = x0; x != x1; x += xstep) {
		if (steep) {
			xDraw = y;
			yDraw = x;
		} else {
			xDraw = x;
			yDraw = y;
		}
		putPixel(xDraw, yDraw, color);
		if (E > 0) {
			E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
			y = y + ystep;
		} else {
			E += TwoDy; //E += 2*Dy;
		}
	}
}

template<typename T>
void Image2d<T>::resize(size_t x, size_t y)
{
	_x = x;
	_y = y;
	_array.resize(_x*_y);
}

template<typename T>
Image2d<T>::Image2d(size_t x, size_t y):
	_x(x), _y(y)
{
	_array.resize(_x*_y);
}

} // namespace ggl

#endif /* IMAGE2D_H_ */
