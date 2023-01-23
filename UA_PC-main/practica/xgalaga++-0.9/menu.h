#ifndef MENU_H
#define MENU_H

#include "gfxinterface.h"
#include <string>
#include <vector>


class StartMenu {
	static StartMenu * singleton_;

	XFontStruct * font_;
	int text_width_;
	int wait_scores_;    // time to wait before score/help auto-switch
	bool print_scores_;  // Is scores or help menu displayed?
	int scroll_scores_;  // Scroll down scores this many lines
	bool can_scroll_;    // Can scroll down?
	Coord last_window_size_;
	std::vector<std::string> score_lines_;
	unsigned short rGb_; // for color cycling
	short rGb_add_;      // for color cycling

	StartMenu();
	~StartMenu();
	XColor NextColor();
	int LineHeight() const { return font_->ascent + font_->descent + 1; }
	void PrintHelp(XColor color);
	void PrintScores(XColor color);
public:
	static StartMenu & Instance();
	static void DestroyInstance() { delete singleton_; singleton_ = 0; }

	bool Display();
private:
	void SetFontContext(XColor &) const;
};


#endif
