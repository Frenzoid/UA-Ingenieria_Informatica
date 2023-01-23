#include "managers.h"
#include "xpms.h"
#include <algorithm>
#include <cstdlib>
#include <stdexcept>


template <class Ctn> inline void Delete(typename Ctn::value_type ptr)
{
	delete ptr;
}


/*
 * ConvoyData
 */

int ConvoyData::ConvoySize() const
{
	return X11::Inst().WindowWidth() * convoy_size_pc / g_aliens_hspacing / 100;
}



/*
 *  BulletsManager
 */
 
BulletsManager::~BulletsManager()
{
	std::for_each(bullets_.begin(), bullets_.end(), Delete<BulletsCtn>);
}


void BulletsManager::Move()
{
	BulletsCtn::iterator it (bullets_.begin());
	while (it != bullets_.end()) {
		(*it)->Move();
		if ((*it)->Out()) {
			delete *it;
			it = bullets_.erase(it);
		}
		else {
			++it;
		}
	}
}


void BulletsManager::Add(const Pix * pix, Coord pos, Coord speed)
{
	bullets_.push_back(new Projectile (pix, pos, speed));
}


int BulletsManager::DoCollisions(const Sprite & other, int max)
{
	int res (0);
	BulletsCtn::iterator it (bullets_.begin());
	while (res < max && it != bullets_.end()) {
		if ((*it)->Collide(other)) {
			++res;
			(*it)->Mask();
			delete *it;
			it = bullets_.erase(it);
		}
		else {
			++it;
		}
	}
	return res;
}



/*
 *  BonusManager
 */
 
BonusManager::~BonusManager()
{
	std::for_each(bonuses_.begin(), bonuses_.end(), Delete<BonusCtn>);
}


void BonusManager::Move()
{
	BonusCtn::iterator it (bonuses_.begin());
	while (it != bonuses_.end()) {
		(*it)->Move();
		if ((*it)->Out()) {
			delete *it;
			it = bonuses_.erase(it);
		}
		else {
			++it;
		}
	}
}


void BonusManager::Add(Coord pos, Bonus::bonus_t type)
{
	bonuses_.push_back(new Bonus (pos, type));
}


Bonus::bonus_t BonusManager::GetBonusCollision(const Sprite & other)
{
	BonusCtn::iterator it (bonuses_.begin());
	while (it != bonuses_.end()) {
		if ((*it)->Collide(other)) {
			const Bonus::bonus_t res ((*it)->Type());
			(*it)->Mask();
			delete *it;
			bonuses_.erase(it);
			return res;
		}
		++it;
	}
	return Bonus::none;
}



/*
 *  ExplosionsManager
 */

ExplosionsManager::~ExplosionsManager()
{
	std::for_each(explosions_.begin(), explosions_.end(), Delete<ExplosionsCtn>);
}


void ExplosionsManager::Move()
{
	ExplosionsCtn::iterator it (explosions_.begin());
	while (it != explosions_.end()) {
		(*it)->Move();
		if ((*it)->Finished()) {
			delete *it;
			it = explosions_.erase(it);
		}
		else {
			++it;
		}
	}
}


void ExplosionsManager::Add(Coord pos, Coord speed, XColor color, int duration)
{
	explosions_.push_back(new Explosion (pos, speed, color, duration));
}



/*
 *  AliensManager
 */

static int GetNbConvoys(const ConvoyData * convoys)
{
	const ConvoyData * p (convoys);
	while (p->alien_xpm) ++p;
	return p - convoys;
}


int AliensManager::bonus_wait_;


AliensManager::AliensManager(BulletsManager * bombs_manager,
                             BulletsManager * bullets_manager,
                             BonusManager * bonus_manager,
                             ExplosionsManager * explosions_manager,
                             int level_number, const ConvoyData * convoys_data,
                             int max_level)
: bombs_manager_     (bombs_manager)
, bullets_manager_   (bullets_manager)
, bonus_manager_     (bonus_manager)
, explosions_manager_(explosions_manager)
, level_number_      (level_number)
, convoys_           (convoys_data)
, nconvoys_          (GetNbConvoys(convoys_data))
, max_convoy_size_   (GetMaxConvoySize())
, convoy_idx_        (0)
, speed_             (level_number / (max_level + 1) + 3)
, base_cruise_       (0, g_alien_height)
, base_cruise_speed_ (1)
, next_creation_     (new_convoy)
{
	if (level_number_ < 1 || !convoys_ || !convoys_[0].alien_xpm) {
		throw std::invalid_argument ("AliensManager data error");
	}
	next_creation_wait_ = convoys_[0].wait;
	if (level_number_ == 1) bonus_wait_ = 20;
}


int AliensManager::GetMaxConvoySize() const
{
	int res (0);
	for (int i (0); i < nconvoys_; ++i) {
		const int convoy_size (convoys_[i].ConvoySize());
		if (convoy_size > res) res = convoy_size;
	}
	return res;
}


AliensManager::~AliensManager()
{
	std::for_each(aliens_.begin(), aliens_.end(), Delete<AliensCtn>);
}


void AliensManager::Move() {
	base_cruise_.x += base_cruise_speed_;
	if ((base_cruise_speed_ < 0 && base_cruise_.x <= g_alien_width / 2) ||
	    (base_cruise_speed_ > 0 && base_cruise_.x >= X11::Inst().WindowWidth() -
	    g_alien_width / 2 - (max_convoy_size_ - 1) * g_aliens_hspacing)) {
		base_cruise_speed_ *= -1;
	}

	for (std::list<Alien*>::iterator it (aliens_.begin()); it != aliens_.end(); ++it) {
		(*it)->Move();
	}

	if (next_creation_wait_ == 0) {
		Creation();
	}
	else {
		--next_creation_wait_;
	}
}


void AliensManager::Creation()
{
	switch (next_creation_) {
	case new_convoy:
		convoy_alien_idx_ = 0;
		next_creation_ = new_alien;
		// Falls through.
	case new_alien: {
		const ConvoyData *const convoy (convoys_ + convoy_idx_);
		const Coord delta_cruise ((convoy_alien_idx_ + (max_convoy_size_ - convoy->ConvoySize()) / 2) * g_aliens_hspacing,
		                          (nconvoys_ - convoy_idx_ - 1) * g_aliens_vspacing);
		const bool mirrored (convoy->x_mirror ^ (convoy->split && convoy_alien_idx_ % 2 == 0));
		aliens_.push_back(new Alien (PixKeeper::Instance().Get(convoy->alien_xpm),
		                             Trajectory (convoy->arrival, mirrored, base_cruise_, delta_cruise),
		                             speed_));

		if (++convoy_alien_idx_ < convoy->ConvoySize()) {
			next_creation_wait_ = 30 / speed_;
		} else {
			++convoy_idx_;
			if (convoy_idx_ < nconvoys_) {
				next_creation_ = new_convoy;
				next_creation_wait_ = convoys_[convoy_idx_].wait;
			} else {
				next_creation_ = new_attack;
				next_creation_wait_ = std::max(50, 750 - level_number_ * 33);
			}
		}
		break;
	}
	case new_attack: {
		int nb_attacking (0);
		for (AliensCtn::const_iterator it (aliens_.begin()); it != aliens_.end(); ++it) {
			if ((*it)->Stage() == Trajectory::attacking) ++nb_attacking;
		}
		for (AliensCtn::iterator it (aliens_.begin());
		     it != aliens_.end() && nb_attacking < level_number_ * 3;
		     ++it) {
			if ((*it)->Stage() == Trajectory::cruising) {
				(*it)->BuildAttack();
				++nb_attacking;
			}
		}
		next_creation_wait_ = 5;
	}
	} // switch
}


void AliensManager::Fire() const
{
	for (AliensCtn::const_iterator it (aliens_.begin());
	     it != aliens_.end() &&
	     bombs_manager_->Nb() < 3 * level_number_ * max_convoy_size_ / 12;
	     ++it) {
		if ((*it)->Stage() != Trajectory::cruising &&
		    (*it)->Stage() != Trajectory::joining &&
		    std::rand() % 50 < speed_) {
			const int bomb_speed_x (std::rand() % 3 + std::rand() % 3 - 2);
			const Coord bomb_speed (bomb_speed_x, speed_ * 3 / 2 - std::abs(bomb_speed_x));
			bombs_manager_->Add(PixKeeper::Instance().Get(bomb_xpm),
			                    (*it)->CannonPosition(),
			                    bomb_speed);
		}
	}
}


int AliensManager::DoBulletsCollisions()
{
	int nb (0);
	AliensCtn::iterator it (aliens_.begin());
	while (it != aliens_.end()) {
		if (bullets_manager_->DoCollisions(**it, 1)) {
			// alien explosion and bonus creation (maybe)
			(*it)->Mask();
			XColor color;
			color.red = color.green = 65535; color.blue = 54*1024;
			explosions_manager_->Add((*it)->Position(), Coord(0,-4), color);
			CreateBonusMaybe((*it)->Position());
			++nb;
			delete *it;
			it = aliens_.erase(it);
		}
		else {
			++it;
		}
	}
	return nb;
}


void AliensManager::CreateBonusMaybe(Coord pos)
{
	static Bonus::bonus_t bonuses[] = {
		Bonus::extra_speed,
		Bonus::extra_speed,
		Bonus::extra_speed,
		Bonus::extra_speed,
		Bonus::extra_fire,
		Bonus::extra_fire,
		Bonus::extra_fire,
		Bonus::extra_fire,
		Bonus::extra_fire,
		Bonus::extra_multi,
		Bonus::extra_multi,
		Bonus::extra_shield,
		Bonus::extra_shield,
	};
	static size_t created = 0;
	if (--bonus_wait_ > 0) return;
	if (created % (sizeof bonuses / sizeof bonuses[0]) == 0) {
		created = 0;
		std::random_shuffle(&bonuses[0], &bonuses[sizeof bonuses / sizeof bonuses[0]]);
	}
	bonus_wait_ = max_convoy_size_ * 5;
	bonus_manager_->Add(pos, bonuses[created++]);
}


/*
 *  Player
 */

Player::Player(BulletsManager * bullets_manager,
               BulletsManager * bombs_manager,
               BonusManager * bonus_manager,
               ExplosionsManager * explosions_manager,
               int below_y)
: Sprite             (PixKeeper::Instance().Get(player_xpm),
                      Coord(X11::Inst().WindowWidth() / 2, -50))
, bullets_manager_   (bullets_manager)
, bombs_manager_     (bombs_manager)
, bonus_manager_     (bonus_manager)
, explosions_manager_(explosions_manager)
, below_y_           (below_y)
, shield_            (3)
, speed_             (2)
, fire_wait_         (0)
, fire_interval_     (24)
, multi_fire_        (1)
{
}


void Player::Move(int direction)
{
	if (fire_wait_ > 0) --fire_wait_;

	Coord pos (Position());
	pos.x += direction * speed_;
	if (pos.x < Width() / 2) pos.x = Width() / 2;
	else {
		const int max_right (X11::Inst().WindowWidth() - Width() / 2 - 1);
		if (pos.x > max_right) pos.x = max_right;
	}
	pos.y = PosY();
	MoveTo(pos);
}


void Player::Fire()
{
	if (fire_wait_ > 0) return;	
	fire_wait_ = fire_interval_;

	for (int i (0); i < multi_fire_; ++i) {
		Coord speed (i - multi_fire_ / 2, -10);
		if (multi_fire_ % 2 == 0 && i >= multi_fire_ / 2) ++speed.x;
		Coord fire_pos (Position());
		fire_pos.y -= Height() / 2;
		bullets_manager_->Add(PixKeeper::Instance().Get(bullet_xpm),
		                      fire_pos,
		                      speed);
	}
}


void Player::DoBombsCollisions()
{
	for (int n (bombs_manager_->DoCollisions(*this, shield_ + 1)); n; --n) {
		--shield_;
		XColor color;
		color.blue = 65535; color.red = color.green = 54*1024;
		explosions_manager_->Add(Position(), Coord(0,0), color, 50);
	}
}


void Player::DoBonusCollisions()
{
	Bonus::bonus_t res;
	while ((res = bonus_manager_->GetBonusCollision(*this)) != Bonus::none) {
		switch (res) {
		case Bonus::extra_speed:
			ExtraSpeed();
			break;
		case Bonus::extra_fire:
			ExtraFire();
			break;
		case Bonus::extra_multi:
			ExtraMulti();
			break;
		case Bonus::extra_shield:
			ExtraShield();
			break;
		default:
			break;
		}
	}
}


int Player::PosY() const
{
	return X11::Inst().WindowHeight() - below_y_ - Height() / 2;
}


void Player::ExtraFire()
{
	if (fire_interval_ > 5) {
		fire_interval_ = fire_interval_ * 3 / 4;
		fire_wait_ = fire_wait_ * 3 / 4;
	}
}


void Player::ExtraMulti()
{
	if (multi_fire_ < 9) {
		fire_interval_ = fire_interval_ * (multi_fire_ + 1) / multi_fire_;
		fire_wait_ = fire_wait_ * (multi_fire_ + 1) / multi_fire_;
		++multi_fire_;
	}
}
