#ifndef MANAGERS_H
#define MANAGERS_H

#include "constants.h"
#include "explosion.h"
#include "sprites.h"
#include <limits>
#include <list>
#include <utility>
#include <vector>


// An aliens convoy is defined by the vessel, the number of
// vessels and the formation (that can be X-mirrored)
struct ConvoyData {
	const int wait;
	const char *const *const alien_xpm;
	const int convoy_size_pc;
	const RCoord *const arrival;
	const bool x_mirror;
	const bool split;

	int ConvoySize() const;
};


class BulletsManager {
	typedef std::list<Projectile*> BulletsCtn;
	BulletsCtn bullets_;
public:
	~BulletsManager();
	void Move();
	void Add(const Pix * pix, Coord pos, Coord speed);
	int DoCollisions(const Sprite & other, int max);
	int Nb() const { return bullets_.size(); }
};


class BonusManager {
	typedef std::list<Bonus*> BonusCtn;
	BonusCtn bonuses_;
public:
	~BonusManager();
	void Move();
	void Add(Coord pos, Bonus::bonus_t type);
	Bonus::bonus_t GetBonusCollision(const Sprite & other);
};


class ExplosionsManager {
	typedef std::list<Explosion*> ExplosionsCtn;
	ExplosionsCtn explosions_;
public:
	~ExplosionsManager();
	void Move();
	void Add(Coord pos, Coord speed, XColor color, int duration = 24);
};


// Aliens arrive in convoys. The AlienManager creates aliens according
// to convoys data and then move and destroy them if collision.
class AliensManager {
	static int bonus_wait_;

	BulletsManager *const bombs_manager_;
	BulletsManager *const bullets_manager_;
	BonusManager *const bonus_manager_;
	ExplosionsManager *const explosions_manager_;
	const int level_number_;
	const ConvoyData *const convoys_;
	const int nconvoys_;
	const int max_convoy_size_;
	int convoy_idx_;
	int convoy_alien_idx_;
	const int speed_;
	Coord base_cruise_;
	int base_cruise_speed_;
	enum creation_t { new_convoy, new_alien, new_attack };
	creation_t next_creation_;
	int next_creation_wait_;
	typedef std::list<Alien*> AliensCtn;
	AliensCtn aliens_;
public:
	AliensManager(BulletsManager * bombs_manager,
	              BulletsManager * bullets_manager,
	              BonusManager*, ExplosionsManager*,
	              int level_number, const ConvoyData * convoysdata,
	              int max_level);
	~AliensManager();
	void Move();
	void Fire() const;
	int  DoBulletsCollisions();
	bool Finished() const
		{ return next_creation_ == new_attack && aliens_.empty(); }
private:
	int GetMaxConvoySize() const;
	void Creation();
	void CreateBonusMaybe(Coord);
};


// The player ship is displayed by a pix and moves on the bottom of the window.
// It can fire bullets. It can collide with alien bullets (bombs) and bonuses.
// The shield is decremented by each collision.
class Player : public Sprite {
	Player(const Player &); // no copy
	Player & operator=(const Player &); // no copy

	BulletsManager *const bullets_manager_;
	BulletsManager *const bombs_manager_;
	BonusManager *const bonus_manager_;
	ExplosionsManager *const explosions_manager_;
	const int below_y_;
	int shield_;
	int speed_;
	int fire_wait_, fire_interval_;
	int multi_fire_;
public:
	Player(BulletsManager * bullets_manager, BulletsManager * bombs_manager,
	       BonusManager*, ExplosionsManager*, int below_y);
	void Move(int direction);
	void Fire();
	void DoBombsCollisions();
	void DoBonusCollisions();
	int  Shield() const { return shield_; }
	void ExtraFire();
	void ExtraMulti();
	void ExtraShield() { ++shield_; }
	void ExtraSpeed() { ++speed_; }
private:
	int  PosY() const;
};

#endif
