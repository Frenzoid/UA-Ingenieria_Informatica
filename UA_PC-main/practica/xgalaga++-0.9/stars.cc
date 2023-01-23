#include "stars.h"
#include "config.h"
#include "instance.h"
#include <algorithm>
#include <cstdlib>
#include <stdexcept>


/*
 * StarsFields::StarsField
 */

StarsFields::StarsField::StarsField(int speed)
: speed_(speed)
{
	if (speed < 1) throw std::range_error ("Illegal star speed");
	// slow stars are farther => dimmer
	color_.red = color_.green = color_.blue =
		std::min(65535u, 20000u + (speed_ * speed_) * 5000);
	X11::Inst().AllocColorAlways(&color_);
}


void StarsFields::StarsField::Scroll()
{
	static unsigned count = 0;

	// Erase existing stars.
	X11::Inst().SetClipMask(None);
	X11::Inst().SetForeground(X11::Inst().GetBlack());
	DrawAll();

	// Scroll existing stars, destroying out of window ones.
	for (FieldCtn::size_type i = 0; i < field_.Size(); ++i) {
		field_[i].y += speed_;
	}
	while (field_.Size() > 0 && field_[0].YOut()) {
		field_.Pop();
	}

	// Create one star in an (empty) top line on pair 'count'.
	if (count++ & 1) {
		const Coord star (std::rand() % X11::Inst().WindowWidth(),
		                  std::rand() % speed_);
		field_.Push(star);
	}

	// Draw all stars
	X11::Inst().SetForeground(color_.pixel);
	DrawAll();
}


void StarsFields::StarsField::DrawAll() const
{
	if (field_.Vector1Size() > 0) {
		X11::Inst().DrawPoints(field_.Vector1(),
		                       field_.Vector1Size());
		if (field_.Vector2Size() > 0) {
			X11::Inst().DrawPoints(field_.Vector2(),
			                       field_.Vector2Size());
		}
	}
}



/*
 * StarsFields
 */
 
StarsFields * StarsFields::singleton_ (0);
const int StarsFields::max_star_speed_;


StarsFields & StarsFields::Instance()
{
	if (!singleton_) {
		singleton_ = new StarsFields;
		InstancesManager::Instance().Push(DestroyInstance);
	}
	return *singleton_;
}


void StarsFields::DestroyInstance()
{
	delete singleton_;
	singleton_ = 0;
}


StarsFields::StarsFields()
{
	for (int speed (1); speed <= max_star_speed_; ++speed) {
		stars_fields_.push_back(new StarsField(speed));
	}	
}


StarsFields::~StarsFields()
{
	for (Ctn::iterator it (stars_fields_.begin());
	     it != stars_fields_.end(); ++it) {
		delete *it;
	}
}


void StarsFields::Scroll()
{
	int nb (Config::Instance().ScaleDetails(max_star_speed_));
	for (Ctn::iterator it (stars_fields_.begin());
	     it != stars_fields_.end() && nb > 0;
	     ++it, --nb) {
		(*it)->Scroll();
	}
}
