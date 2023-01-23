#include "explosion.h"
#include "config.h"
#include <cstdlib>


/*
 *  Explosion
 */

Explosion::Explosion(Coord pos, Coord speed, XColor color, int duration)
: color_   (color)
, moves_   (0)
, duration_(duration)
{
	const int nb_dots (Config::Instance().ScaleDetails(16 * duration));
	dots_.reserve(nb_dots);
	dots_speed_.reserve(nb_dots);
	for (int i (0); i < nb_dots; ++i) {
		using std::rand;
		const Coord particle (rand() % 16 + rand() % 16 - 16,
		                      rand() % 16 + rand() % 16 - 16);
		dots_.push_back(particle + pos);
		Coord particle_speed (particle / 4 + speed);
		particle_speed += Coord(rand() % 5 - 2, rand() % 5 - 2);
		dots_speed_.push_back(particle_speed);
	}
	XColor close_color = color_;
	X11::Inst().AllocColorAlways(&close_color);
	DrawAll(close_color.pixel);
}


void Explosion::Move()
{
	if (moves_ < duration_) {
		++moves_;
		DrawAll(X11::Inst().GetBlack());
		if (moves_ < duration_) {
			for (dotsCtn::size_type i (0); i < dots_.size(); ++i) {
				dots_[i] += dots_speed_[i];
			}
			color_.red   = color_.red   * 98 / 100;
			color_.green = color_.green * 96 / 100;
			color_.blue  = color_.blue  * 96 / 100;
			if (color_.red < 48*1024 && color_.red > 36*1024) {
				color_.red   = color_.red   * 96 / 100;
				color_.green = color_.green * 92 / 100;
				color_.blue  = color_.blue  * 92 / 100;
			}
			XColor close_color = color_;
			X11::Inst().AllocColorAlways(&close_color);
			DrawAll(close_color.pixel);
		}
	}
}


void Explosion::DrawAll(X11::Color color) const
{
	X11::Inst().SetForeground(color);
	X11::Inst().SetClipMask(None);
	X11::Inst().DrawPoints(&dots_[0], dots_.size());
}
