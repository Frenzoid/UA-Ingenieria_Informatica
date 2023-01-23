#include "score.h"
#include "instance.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>


Score * Score::singleton_ (0);


Score & Score::Instance()
{
	if (!singleton_) {
		singleton_ = new Score;
		InstancesManager::Instance().Push(DestroyInstance);
	}
	return *singleton_;
}


void Score::DestroyInstance()
{
	delete singleton_;
	singleton_ = 0;
}


Score::Score()
: score_ (0)
, shield_(-1)
, level_ (0)
, font_  (X11::Inst().LoadQueryFont("*-helvetica-*-r-*-*-12-*"))
{
	if (!font_) {
		font_ = X11::Inst().LoadQueryFont("fixed");
		if (!font_) throw std::runtime_error ("X font error");
	}
	pos_ = Coord(2, PosY());
	color_.red = color_.green = 48 * 1024;
	color_.blue = 65535;
	X11::Inst().AllocColorAlways(&color_);
	Draw();
}


Score::~Score()
{
	X11::Inst().FreeFont(font_);
}


void Score::Draw()
{
	X11::Inst().SetClipMask(None);
	X11::Inst().SetForeground(color_.pixel);
	std::ostringstream ost;
	ost << "level: " << std::setw(2) << std::setfill(' ') << level_
	    << "  score: " << std::setw(4) << std::setfill('0') << score_;
	if (shield_ >= 0) ost << "   shield: " << std::string(shield_, '»');
	old_text_ = ost.str();
	pos_.y = PosY();
	X11::Inst().SetFont(font_->fid);
	X11::Inst().DrawString(pos_, old_text_);
}


void Score::Mask() const
{
	X11::Inst().SetClipMask(None);
	X11::Inst().SetForeground(X11::Inst().GetBlack());
	X11::Inst().SetFont(font_->fid);
	X11::Inst().DrawString(pos_, old_text_);
}


void Score::DrawLevel(X11::Color color) const
{
	X11::Inst().SetClipMask(None);
	X11::Inst().SetForeground(color);
	X11::Inst().SetFont(font_->fid);
	Coord pos (RCoord(512, 512));
	std::ostringstream ost;
	ost << "LEVEL " << level_;	
	pos.x -= XTextWidth(font_, ost.str().c_str(), ost.str().size()) / 2;
	X11::Inst().DrawString(pos, ost.str());
}


int Score::PosY() const
{
	return X11::Inst().WindowHeight() - font_->descent;
}
