#include "sprites.h"
#include "config.h"
#include "constants.h"
#include "xpms.h"
#include <cstdlib>
#include <stdexcept>



/*
 *  Sprite
 */

Sprite::Sprite(const Pix * pix, Coord pos)
: pix_(pix)
, pos_(pos)
{
	if (!pix) throw std::invalid_argument ("Null pixmap for sprite");
	Draw();
}


bool Sprite::Collide(const Sprite & other) const
{
	// Collision if the horizontal/vertical distance is smaller than the addition
	// of half Widths/Heights.
	return std::abs(pos_.x - other.pos_.x) * 2 < Width()  + other.Width() &&
	       std::abs(pos_.y - other.pos_.y) * 2 < Height() + other.Height();
}


void Sprite::MoveTo(Coord to)
{
	pix_->Move(pos_, to);
	pos_ = to;
}



/*
 *  Projectile
 */

bool Projectile::Out() const
{
	return Position().y - Height() / 2 + Height() < 0 ||
	       Position().y - Height() / 2 >= X11::Inst().WindowHeight();
}



/*
 *  Bonus
 */

// To be synchronized with bonus types enum in .h file.
static const char *const * bonus2pix[] =
	{ 0, bonus_speed_xpm, bonus_fire_xpm, bonus_shield_xpm, bonus_multi_xpm };

Bonus::Bonus(Coord pos, bonus_t type)
: Projectile(PixKeeper::Instance().Get(bonus2pix[type]), pos, Coord(0, 1))
, type_(type)
{}



/*
 *  Trajectory
 */

Trajectory::Trajectory(const RCoord * arrival,
                       bool mirrored,
                       const Coord & base_cruise,
                       Coord delta_cruise)
: stage_       (arriving)
, arrival_     (arrival)
, mirrored_    (mirrored)
, base_cruise_ (base_cruise)
, delta_cruise_(delta_cruise)
{
	if (!arrival || *arrival == RCEnd) {
		throw std::invalid_argument ("Empty arrival trajectory");
	}
}


Coord Trajectory::NextPosition(Coord from, int velocity)
{
	if (velocity == 0) return from;

	switch (stage_) {
	case arriving: {
		const Coord goal (mirrored_ ? arrival_->XMirror() : *arrival_);
		const Coord delta (goal - from);
		const double scale (delta.Length() / velocity);
		if (scale < 1.0) {
			if (*(++arrival_) == RCEnd) stage_ = joining;
			return NextPosition(from, velocity);
		}
		return from + delta / scale;
	}
	case joining: {
		const Coord cruise_pos (base_cruise_ + delta_cruise_);
		const Coord delta (cruise_pos - from);
		const double scale (delta.Length() / velocity);
		if (scale <= 1.0) {
			stage_ = cruising;
			return cruise_pos;
		}
		return from + delta / scale;
	}
	case cruising:
		return base_cruise_ + delta_cruise_;
	case attacking: default: {
		const Coord delta (*attack_it_ - from);
		const double scale (delta.Length() / (velocity - 1));
		if (scale < 1.0) {
			if (++attack_it_ == attack_.end()) {
				attack_.clear();
				stage_ = joining;
				from.y = -g_alien_height;
				return from;
			}
			return NextPosition(from, velocity);
		}
		return from + delta / scale;
	}
	} // switch
}


void Trajectory::BuildAttack(Coord from)
{
	const int min_delta_y (RCoord::max / 64);
	attack_.reserve(RCoord::max / min_delta_y);
	RCoord next (from.ToRCoord());
	do {
		next += RCoord(std::rand() % (RCoord::max/3) - RCoord::max/3/2,
		               std::rand() % (RCoord::max/4) + min_delta_y);
		attack_.push_back(next);
	} while (!next.YOut());
	attack_it_ = attack_.begin();
	stage_ = attacking;
}



/*
 *  Alien
 */

Alien::Alien(const Pix * pix, const Trajectory & trajectory, int speed)
: Sprite     (pix, trajectory.InitPosition())
, trajectory_(trajectory)
, speed_     (speed)
{
}


void Alien::Move()
{
	MoveTo(trajectory_.NextPosition(Position(), speed_));
}


Coord Alien::CannonPosition() const
{
	Coord pos (Position());
	pos.y += Height() - (Height() / 2);
	return pos;
}
