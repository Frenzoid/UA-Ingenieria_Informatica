#ifndef SCORE_H
#define SCORE_H

#include "gfxinterface.h"
#include <string>


class Score {
	static Score * singleton_;

	int score_;
	int shield_;
	int level_;
	Coord pos_;
	XFontStruct * font_;
	XColor color_;
	std::string old_text_;

	Score();
	~Score();
public:
	static Score & Instance();
	static void DestroyInstance();

	int  Value() const { return score_; }
	void Add(int i) { score_ += i; }
	void IncLevel() { ++level_; }
	void SetShield(int i) { shield_ = i; }
	void ReInit()  { score_ = 0; level_ = 1; }
	void Refresh() { Mask(); Draw(); }
	int  Level()  const { return level_; }
	void ShowLevel() const { DrawLevel(color_.pixel); }
	void EraseLevel() const	{ DrawLevel(X11::Inst().GetBlack()); }
	int  Height() const { return font_->descent + font_->ascent; }
private:
	void Draw();
	void DrawLevel(X11::Color) const;
	void Mask() const;
	int  PosY() const;
};


#endif
