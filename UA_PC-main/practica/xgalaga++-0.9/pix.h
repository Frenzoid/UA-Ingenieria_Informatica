#ifndef PIX_H
#define PIX_H

#include "gfxinterface.h"
#include <map>


// Picture defined by two pixmaps: one for colors; one for tranparency (shape).
// The constructors loads it in the X server and it can then be displayed an
// arbitrary number of times.
class Pix {
	Pixmap pixmap_, shapemask_;
	Coord dim_;

	Pix(const Pix &); // no copy
	Pix & operator=(const Pix &); // no assign

	friend class PixKeeper;
	Pix(const char *const * xpm);
	~Pix();
public:
	int Width()  const { return dim_.x;  }
	int Height() const { return dim_.y; }
	Coord Dim()  const { return dim_; }
	void Draw(Coord pos) const;
	void Mask(Coord pos) const;
	void Move(Coord from, Coord to) const;
};


// Singleton that initializes and keep Pix's.
class PixKeeper {
	static PixKeeper * singleton_;

	PixKeeper() {}
	~PixKeeper();
	PixKeeper(const PixKeeper &); // no copy
	PixKeeper & operator=(const PixKeeper &); // no copy

	typedef std::map<const char *const *, const Pix *> PixCtn;
	PixCtn pixes_;
public:
	static PixKeeper & Instance();
	static void DestroyInstance();

	const Pix * Get(const char *const * pix_data);
};

#endif
