#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gfxinterface.h"
#include <vector>


// An explosion is made of moving, color changing, dots.
class Explosion {
	XColor color_;
	int moves_;
	const int duration_;
	typedef std::vector<Coord> dotsCtn;
	dotsCtn dots_, dots_speed_;
public:
	Explosion(Coord pos, Coord speed, XColor color, int duration = 24);
	void Move();
	bool Finished() const { return moves_ >= duration_; }
private:
	void DrawAll(X11::Color color) const;
};


#endif
