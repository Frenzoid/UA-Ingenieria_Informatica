#ifndef SPRITES_H
#define SPRITES_H

#include "gfxinterface.h"
#include "pix.h"
#include <vector>


// A sprite is defined by a Pix and a position.
class Sprite {
	const Pix * pix_;
	Coord pos_;
public:
	Sprite(const Pix * pix, Coord pos);
	virtual ~Sprite() {}
	Coord Position() const { return pos_; }
	int Width()      const { return pix_->Width(); }
	int Height()     const { return pix_->Height(); }
	Coord Dim()      const { return pix_->Dim(); }
	void Mask()      const { pix_->Mask(pos_); }
	void Draw()      const { pix_->Draw(pos_); }
	bool Collide(const Sprite & other) const;
protected:
	void MoveTo(Coord to);
};


// Projectile is the base class for constant speed moving objects.
class Projectile : public Sprite {
	const Coord speed_;
public:
	Projectile(const Pix * pix, Coord pos, Coord speed)
		: Sprite(pix, pos), speed_(speed) {}
	void Move() { MoveTo(Position() + speed_); }
	bool Out() const;
};


// They are several bonus types, all dropping the same way.
class Bonus : public Projectile {
public:
	// To be synchronized with bonus to pix table in .cc file.
	enum bonus_t { none=0, extra_speed=1, extra_fire=2, extra_shield=3,
	               extra_multi=4 };
private:
	const bonus_t type_;
public:
	Bonus(Coord pos, bonus_t type);
	bonus_t Type() const { return type_; }
};


// One trajectory is given to each Alien. The trajectory computes
// Aliens positions. The position may be X-mirrored (for split convoys).
// The Trajectory can build an attack.
// A trajectory has 4 stages:
// - an arriving stage consisting of passing through given RCoord's;
// - a joining stage to join the cruising position;
// - a cruising stage at position given by a changing base and a fixed delta;
// - an attacking stage consisting of passing through random RCoord's.
class Trajectory {
public:
	enum stage_t { arriving, joining, cruising, attacking };
private:
	stage_t stage_;              // current trajectory stage
	const RCoord * arrival_;     // table of RCoord's, RCEnd terminated
	const bool mirrored_;        // Use X-mirrored RCoord's?
	const Coord & base_cruise_;  // Ref to var updated with cruise position
	const Coord delta_cruise_;   // delta from base cruise postion
	std::vector<RCoord> attack_; // keep built attack trajectory
	std::vector<RCoord>::const_iterator attack_it_;  // current attack pos
public:
	Trajectory(const RCoord * arrival,
	           bool mirrored,
	           const Coord & base_cruise,
	           Coord delta_cruise);
	stage_t Stage() const { return stage_; }
	Coord NextPosition(Coord from, int velocity);
	Coord InitPosition() const
		{ return mirrored_ ? arrival_[0].XMirror() : arrival_[0]; }
	void BuildAttack(Coord from);
};


// An alien vessel is displayed by a pix at a position given by its trajectory.
// It can fire bullets (dropping bombs). It can collide with player bullets.
class Alien : public Sprite {
	Trajectory trajectory_;
	const int speed_;
public:
	Alien(const Pix * pix, const Trajectory & trajectory, int speed);
	void Move();
	Coord CannonPosition() const;
	Trajectory::stage_t Stage() const { return trajectory_.Stage(); }
	void BuildAttack() { trajectory_.BuildAttack(Position()); }
};

#endif
