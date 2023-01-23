#include "gfxinterface.h"
#include "instance.h"
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <vector>



/*
 *  Coord
 */

// Implementations of conversions from pixels distances to relative distances.
inline int Rel(int dist, int scale)
	{ return (dist * RCoord::max + scale / 2) / scale; }

inline int UnRel(int r, int scale)
	{ return (r * scale + RCoord::max / 2) / RCoord::max; }


Coord::Coord(RCoord rc)
{
	x = UnRel(rc.x, X11::Inst().WindowWidth());
	y = UnRel(rc.y, X11::Inst().WindowHeight());
}

RCoord Coord::ToRCoord() const
{
	return RCoord(Rel(x, X11::Inst().WindowWidth()),
	              Rel(y, X11::Inst().WindowHeight()));
}

double Coord::Length() const
{
	return std::sqrt(static_cast<double>(x * x + y * y));
}

Coord & Coord::operator*=(double rhs)
{
	x = static_cast<short>(std::floor(x * rhs + 0.5));
	y = static_cast<short>(std::floor(y * rhs + 0.5));
	return *this;
}

Coord & Coord::operator/=(double rhs)
{
	x = static_cast<short>(std::floor(x / rhs + 0.5));
	y = static_cast<short>(std::floor(y / rhs + 0.5));
	return *this;
}



/*
 *  X11
 */

X11 *    X11::singleton_             (0);
unsigned X11::default_window_width_  (640);
unsigned X11::default_window_height_ (480);


void X11::CreateInstance()
{
	if (!singleton_) {
		singleton_ = new X11;
		InstancesManager::Instance().Push(DestroyInstance);
	}
}


X11::X11()
: window_width_ (default_window_width_)
, window_height_(default_window_height_)
{
	display_ = XOpenDisplay(0);
	if (!display_) throw std::runtime_error ("Cannot open display");
	screen_   = DefaultScreen(display_);
	visual_   = DefaultVisual(display_, screen_);
	colormap_ = DefaultColormap(display_, screen_);
	gc_       = DefaultGC(display_, screen_);

	const Color black (BlackPixel(display_, screen_));
	window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_),
	                              0, 0, window_width_, window_height_,
	                              0, black, black);
	XSelectInput(display_, window_, StructureNotifyMask);
	XMapWindow(display_, window_);
	XEvent e;
	do XNextEvent(display_, &e); while (e.type != MapNotify);
	XSelectInput(display_, window_, KeyPressMask | KeyReleaseMask);
}


X11::~X11()
{
	XDestroyWindow(display_, window_);
	XCloseDisplay(display_);
}


void X11::SetWindowTitle(const std::string & title) const
{
	const char *const list_ptr (title.c_str());
 	XTextProperty property;
	if (XStringListToTextProperty(const_cast<char**>(&list_ptr), 1, &property)) {
		XSetWMName(display_, window_, &property);
		XFree(property.value);
	} // Do nothing if out of memory.
}


Status X11::GetWindowAttributes(XWindowAttributes * attrs)
{
	XWindowAttributes attrs2;
	if (!attrs) attrs = &attrs2;
	const Status s (XGetWindowAttributes(display_, window_, attrs));
	if (s != 0) {
		window_width_  = attrs->width;
		window_height_ = attrs->height;
	}
	return s;
}


void X11::ResizeWindow(unsigned width, unsigned height)
{
	GetWindowAttributes();
	if (width != window_width_ || height != window_height_) {
		XEvent e;
		XSelectInput(display_, window_, StructureNotifyMask);
		XResizeWindow(display_, window_, width, height);
		do XNextEvent(display_, &e); while (e.type != ConfigureNotify);
		XSelectInput(display_, window_, KeyPressMask | KeyReleaseMask);
		window_width_  = width;
		window_height_ = height;
	}
}

inline unsigned ColorDistance(const XColor & c1, const XColor & c2)
{
	return std::abs(c1.red   - c2.red  ) +
	       std::abs(c1.green - c2.green) +
	       std::abs(c1.blue  - c2.blue );
}


void X11::AllocColorAlways(XColor * color) const
{
	if (AllocColor(color)) return;

	std::vector<XColor> colors (visual_->map_entries);
	for (std::vector<XColor>::size_type i (0); i < colors.size(); ++i) {
		colors[i].pixel = i;
	}
	XQueryColors(display_, colormap_, &colors[0], colors.size());
	unsigned min_dist (3*65535 + 1);
	std::vector<XColor>::size_type best_index (0);
	for (std::vector<XColor>::size_type i (0); i < colors.size(); ++i) {
		const unsigned dist (ColorDistance(colors[i], *color));
		if (dist < min_dist) {
			min_dist = dist;
			best_index = i;
		}
	}
	// This allocation may fail because the colormap is not locked (and
	// X Window color management is crap).
	// But it looks like it is 1) rare enough 2) quite benign 3) hard to
	// work around, so let it silently fail.
	*color = colors[best_index];
	AllocColor(color);
}


void X11::SetInvisibleCursor(void) {
	Cursor invisibleCursor;
	Pixmap bitmap;
	XColor black;
	static char noData[] = { 0,0,0,0,0,0,0,0 };
	black.red = black.green = black.blue = 0;

	bitmap = XCreateBitmapFromData(display_, window_, noData, 8, 8);
	invisibleCursor = XCreatePixmapCursor(display_, bitmap, bitmap, 
	                                      &black, &black, 0, 0);
	XDefineCursor(display_, window_, invisibleCursor);
	XFreeCursor(display_, invisibleCursor);
	XFreePixmap(display_, bitmap);
}
