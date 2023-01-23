#ifndef X11_H
#define X11_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>
#include <limits>
#include <string>


// Relative coordinates between (0; 0) for top-left and (max-1; max-1)
// for bottom-right.
struct RCoord {
	enum { max = 1024 };
	int x, y;

	RCoord() {}
	RCoord(int _x, int _y) : x(_x), y(_y) {}
	bool XOut() const { return x < 0 || x >= max; }
	bool YOut() const { return y < 0 || y >= max; }
	bool Out() const { return XOut() || YOut(); }
	RCoord XMirror() const { return RCoord(max - x, y); }
	RCoord & operator+=(RCoord rhs)
		{ x += rhs.x; y += rhs.y; return *this; }
	RCoord & operator-=(RCoord rhs)
		{ x -= rhs.x; y -= rhs.y; return *this; }
};

inline RCoord operator+(RCoord lhs, RCoord rhs) { return lhs += rhs; }
inline RCoord operator-(RCoord lhs, RCoord rhs) { return lhs -= rhs; }
inline bool operator==(RCoord lhs, RCoord rhs)
	{ return lhs.x == rhs.x && lhs.y == rhs.y; }

const RCoord RCEnd (std::numeric_limits<int>::max(),
                    std::numeric_limits<int>::max());


// Absolute coordinates, directly useful with X Window functions.
struct Coord : public XPoint {
	Coord() {}
	Coord(short _x, short _y) { x = _x; y = _y; }
	Coord(RCoord);
	RCoord ToRCoord() const;
	bool XOut() const;
	bool YOut() const;
	bool Out() const { return XOut() || YOut(); }
	double Length() const;
	Coord & operator+=(Coord rhs)
		{ x += rhs.x; y += rhs.y; return *this; }
	Coord & operator-=(Coord rhs)
		{ x -= rhs.x; y -= rhs.y; return *this; }
	Coord & operator*=(double rhs);
	Coord & operator/=(double rhs);
	Coord & operator*=(int rhs) {
		x = static_cast<short>(x * rhs);
		y = static_cast<short>(y * rhs);
		return *this;
	}
	Coord & operator/=(int rhs) {
		x = static_cast<short>(x / rhs);
		y = static_cast<short>(y / rhs);
		return *this;
	}
};

inline Coord operator+(Coord lhs, Coord rhs) { return lhs += rhs; }
inline Coord operator-(Coord lhs, Coord rhs) { return lhs -= rhs; }
template<class T> inline Coord operator*(T lhs, Coord rhs)
	{ return rhs *= lhs; }
template<class T> inline Coord operator/(Coord lhs, T rhs)
	{ return lhs /= rhs; }
inline bool operator==(Coord lhs, Coord rhs)
	{ return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(Coord lhs, Coord rhs)
	{ return !(lhs == rhs); }
inline bool operator<(Coord lhs, Coord rhs)
	{ return (lhs.x << 16 | lhs.y) < (rhs.x << 16 | rhs.y); }


// The GUI is a single X window. This class is not an abstraction, it only
// keeps useful data like the X display, screen, visual, colormap...
class X11 {
	static X11 * singleton_;
	static unsigned default_window_width_;
	static unsigned default_window_height_;

	X11();
	~X11();

	Display * display_;
	int screen_;
	Visual * visual_;
	Colormap colormap_;
	GC gc_;
	Window window_;
	unsigned window_width_, window_height_;	// cached values
public:
	typedef unsigned long Color;

	static X11 & Inst();
	static void CreateInstance();
	static void DestroyInstance();
	static void SetDefaultWindowWidth(unsigned);
	static void SetDefaultWindowHeight(unsigned);

	void SetWindowTitle(const std::string & title) const;
	Status GetWindowAttributes(XWindowAttributes * = 0);
	void ResizeWindow(unsigned width, unsigned height);
	int WindowWidth() const;
	int WindowHeight() const;

	void SetInvisibleCursor(void);

	Color GetBlack() const;
	Color GetWhite() const;
	void SetForeground(Color color) const;
	Status AllocColor(XColor *) const;
	void AllocColorAlways(XColor *) const;
	void FreeColor(Color) const;

	void DrawPoint(int x, int y) const;
	void DrawPoint(Coord) const;
	void DrawPoints(const XPoint * points, int npoints) const;
	void SetClipOrigin(int x, int y) const;
	void SetClipOrigin(Coord) const;
	void SetClipMask(Pixmap) const;
	void ClearWindow() const;
	void CopyAreaToWindow(Drawable src, int src_x, int src_y,
	                      unsigned width, unsigned height,
		              int dest_x, int dest_y) const;
	void CopyAreaToWindow(Drawable src, Coord src_c,
	                      Coord dim, Coord dest_c) const;
	void FillRectangle(Coord c, Coord dim) const;

	void NextEvent(XEvent *) const;
	int Pending() const;
	void Sync(Bool discard) const;

	int CreatePixmapFromData(const char *const * xpm, Pixmap * pixmap,
	                         Pixmap * pixmask, XpmAttributes *) const;
	void FreePixmap(Pixmap) const;
	XFontStruct * LoadQueryFont(const std::string & font_name) const;
	void FreeFont(XFontStruct * font) const;
	void SetFont(Font font) const;
	void DrawString(Coord c, const std::string & str) const;
};


inline X11 & X11::Inst()
	{ return *singleton_; }
inline void X11::DestroyInstance()
	{ delete singleton_; singleton_ = 0; }
inline void X11::SetDefaultWindowWidth(unsigned width)
	{ default_window_width_ = width; }
inline void X11::SetDefaultWindowHeight(unsigned height)
	{ default_window_height_ = height; }
inline int X11::WindowWidth() const
	{ return window_width_; }
inline int X11::WindowHeight() const
	{ return window_height_; }
inline X11::Color X11::GetBlack() const
	{ return BlackPixel(display_, screen_); }
inline X11::Color X11::GetWhite() const
	{ return WhitePixel(display_, screen_); }
inline void X11::SetForeground(Color color) const
	{ XSetForeground(display_, gc_, color); }
inline Status X11::AllocColor(XColor * color) const
	{ return XAllocColor(display_, colormap_, color); }
//inline void X11::FreeColor(Color color) const
//	{ XFreeColors(display_, colormap_, &color, 1, 0); }
inline void X11::DrawPoint(int x, int y) const
	{ XDrawPoint(display_, window_, gc_, x, y); }
inline void X11::DrawPoint(Coord c) const
	{ DrawPoint(c.x, c.y); }
inline void X11::DrawPoints(const XPoint * points, int npoints) const
{
	XDrawPoints(display_, window_, gc_, const_cast<XPoint*>(points),
	            npoints, CoordModeOrigin);
}
inline void X11::SetClipOrigin(int x, int y) const
	{ XSetClipOrigin(display_, gc_, x, y); }
inline void X11::SetClipOrigin(Coord c) const
	{ SetClipOrigin(c.x, c.y); }
inline void X11::SetClipMask(Pixmap pixmap) const
	{ XSetClipMask(display_, gc_, pixmap); }
inline void X11::ClearWindow() const
	{ XClearWindow(display_, window_); }
inline void
X11::CopyAreaToWindow(Drawable src, int src_x, int src_y, unsigned width,
                      unsigned height, int dest_x, int dest_y) const
{
	XCopyArea(display_, src, window_, gc_, src_x, src_y,
	          width, height, dest_x, dest_y);
}
inline void
X11::CopyAreaToWindow(Drawable src, Coord src_c, Coord dim, Coord dest_c) const
{
	CopyAreaToWindow(src, src_c.x, src_c.y, dim.x, dim.y,
	                 dest_c.x, dest_c.y);
}
inline void X11::FillRectangle(Coord c, Coord dim) const
	{ XFillRectangle(display_, window_, gc_, c.x, c.y, dim.x, dim.y); }
inline void X11::NextEvent(XEvent * evt) const
	{ XNextEvent(display_, evt); }
inline int X11::Pending() const
	{ return XPending(display_); }
inline void X11::Sync(Bool discard) const
	{ XSync(display_, discard); }
inline int
X11::CreatePixmapFromData(const char *const * xpm, Pixmap * pixmap,
                          Pixmap * pixmask, XpmAttributes * attrs) const
{
	return XpmCreatePixmapFromData(display_, window_,
	                               const_cast<char**>(xpm),
	                               pixmap, pixmask, attrs);
}
inline void X11::FreePixmap(Pixmap pixmap) const
	{ XFreePixmap(display_, pixmap); }
inline XFontStruct * X11::LoadQueryFont(const std::string & font_name) const
	{ return XLoadQueryFont(display_, font_name.c_str()); }
inline void X11::FreeFont(XFontStruct * font) const
	{ XFreeFont(display_, font); }
inline void X11::SetFont(Font font) const
	{ XSetFont(display_, gc_, font); }
inline void X11::DrawString(Coord c, const std::string & str) const
{
	XDrawString(display_, window_, gc_, c.x, c.y, str.c_str(), str.size());
}



inline bool Coord::XOut() const
	{ return x < 0 || x >= X11::Inst().WindowWidth(); }
inline bool Coord::YOut() const
	{ return y < 0 || y >= X11::Inst().WindowHeight(); }


#endif
