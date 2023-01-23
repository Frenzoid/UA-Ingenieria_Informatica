#include "menu.h"
#include "config.h"
#include "constants.h"
#include "gfxinterface.h"
#include "highscore.h"
#include "input.h"
#include "instance.h"
#include "pix.h"
#include "score.h"
#include "stars.h"
#include "time_util.h"
#include "xpms.h"
#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <sstream>


StartMenu * StartMenu::singleton_ (0);


StartMenu & StartMenu::Instance() {
	if (!singleton_) {
		singleton_ = new StartMenu;
		InstancesManager::Instance().Push(DestroyInstance);
	}
	return *singleton_;
}


const char *const menu_lines[] = {
	"XGalaga++ v0.9 (2017-12-10)",
	"©2003-2017 Marc Mongenet, graphics from XGalaga 2.0.34",
	"This game is free software, covered by the GPL.",
	"",
	"Welcome player %p!",
	"",
	"KEY                 ACTION",
	"s                   start game",
	"q                   quit",
	"h                   toggle high scores / menu",
	"p                   pause",
	"1,2,3,4,5           set window size",
	"+                   increase details",
	"-                   decrease details",
	"r                   refresh rate %r1->%r2 Hz",
	"<space bar>         fire",
	"<left/right arrow>  move left/right",
	"<up/down arrow>     scroll high scores up/down",
	"",
	"BONUS",
	"",
	"extra shield every 1000 points"
};


StartMenu::StartMenu()
: font_(X11::Inst().LoadQueryFont("*-fixed-bold-r-*-*-14-*-*-*-*-*-iso8859-1"))
, text_width_      (0)
, wait_scores_     (5000)
, print_scores_    (false)
, scroll_scores_   (0)
, can_scroll_      (true)
, last_window_size_(0, 0)
, rGb_             (0)
, rGb_add_         (1024)
{
	if (!font_) {
		font_ = X11::Inst().LoadQueryFont("*-fixed-*");
		if (!font_) throw std::runtime_error ("X font error");
	}
	for (size_t i (0); i < sizeof menu_lines / sizeof menu_lines[0]; ++i) {
		text_width_ = std::max(text_width_, XTextWidth(font_, menu_lines[i], std::strlen(menu_lines[i])));
	}
}


StartMenu::~StartMenu()
{
	X11::Inst().FreeFont(font_);
}


bool StartMenu::Display()
{
	Input input;
	bool updated (false);
	double frame_time (0);

	for (;;) {

		input.Update();

		if (input.Quit()) return false;

		if (input.Start()) {
			print_scores_ = true;
			wait_scores_ = 5000;
			return true;
		}

		Config::Instance().AddDetailsLevel(input.Details());
		
		if (input.IncRefreshRate()) {
			Config::Instance().SetNextRefreshRate();
			X11::Inst().ClearWindow();
		}
		
		SetStandardWindowSize(input.WindowSize());
		X11::Inst().GetWindowAttributes();

		if (--wait_scores_ < 0 || input.HighScores()) {
			print_scores_ = !print_scores_;
			wait_scores_ = 1000;
			X11::Inst().ClearWindow();
		}

		StarsFields::Instance().Scroll();
		Score::Instance().Refresh();

		if (last_window_size_ != Coord(X11::Inst().WindowWidth(), X11::Inst().WindowHeight())) {
			last_window_size_ = Coord(X11::Inst().WindowWidth(), X11::Inst().WindowHeight());
			scroll_scores_ = 0;
		}

		if (print_scores_) {
			try {
				if (!updated) {
					HighScores::Instance().Update();
					updated = true;
				}
				if (input.VMove()) {
					if (can_scroll_ || input.VMove() < 0) scroll_scores_ += input.VMove();
					if (scroll_scores_ < 0) scroll_scores_ = 0;
					wait_scores_ = 1000;
				}
				PrintScores(NextColor());
			} catch (const std::exception & e) {
				X11::Inst().SetForeground(X11::Inst().GetWhite());
				X11::Inst().SetClipMask(None);
				X11::Inst().SetFont(font_->fid);
				X11::Inst().DrawString(Coord(1, last_window_size_.y / 2), e.what());
			}
		}
		else PrintHelp(NextColor());

		X11::Inst().Sync(False);

		frame_time = SleepTimeInterval(frame_time, 1.0 / Config::Instance().RefreshRate());
	}
}


XColor StartMenu::NextColor()
{
	XColor color;
	color.red = 48*1024;
	color.blue = 65535;
	rGb_ += rGb_add_;
	if (rGb_ == 0) {
		rGb_add_ = -rGb_add_;
		rGb_ += rGb_add_;
	}
	color.green = rGb_;
	return color;
}


void StartMenu::SetFontContext(XColor & color) const
{
	X11::Inst().AllocColorAlways(&color);
	X11::Inst().SetForeground(color.pixel);
	X11::Inst().SetClipMask(None);
	X11::Inst().SetFont(font_->fid);
}


void StartMenu::PrintHelp(XColor color)
{
	Coord pos (std::max(0, (last_window_size_.x - text_width_) / 2), 20);
	SetFontContext(color);

	// Draw help text
	for (size_t i (0); i < sizeof menu_lines / sizeof menu_lines[0]; ++i) {
		std::string line (menu_lines[i]);

		while (line.find("%p") != std::string::npos) {
			line.replace(line.find("%p"), 2, Config::Instance().GetPlayerName());
		}

		std::ostringstream refresh_rate;
		refresh_rate << Config::Instance().RefreshRate();
		while (line.find("%r1") != std::string::npos) {
			line.replace(line.find("%r1"), 3, refresh_rate.str().c_str());
		}

		std::ostringstream next_refresh_rate;
		next_refresh_rate << Config::Instance().NextRefreshRate();
		while (line.find("%r2") != std::string::npos) {
			line.replace(line.find("%r2"), 3, next_refresh_rate.str().c_str());
		}

		X11::Inst().DrawString(pos, line);
		
		pos.y += LineHeight();
		if (line.empty()) {
			color.red -= 8192;
			X11::Inst().AllocColorAlways(&color);
			X11::Inst().SetForeground(color.pixel);
		}
	}
	// Draw bonus pixs with help text
	static const char *const *const bonuses[] =
		{ bonus_speed_xpm, bonus_fire_xpm, bonus_shield_xpm, bonus_multi_xpm };
	static const char *const bonus_text[] =
		{ "extra speed", "extra fire", "extra shield", "multi fire" };
	for (size_t i (0); i < sizeof bonuses / sizeof bonuses[0]; ++i) {
		const Pix *const bonus (PixKeeper::Instance().Get(bonuses[i]));
		bonus->Draw(pos + Coord(bonus->Width() / 2, -bonus->Height() / 2));
		X11::Inst().SetClipMask(None);
		X11::Inst().DrawString(pos + Coord(2 * bonus->Width(), 0), bonus_text[i]);
		pos.y += std::max(bonus->Height(), LineHeight());
	}
}


void StartMenu::PrintScores(XColor color)
{
	Coord pos (std::max(0, (last_window_size_.x - text_width_) / 2), 20);
	SetFontContext(color);
	// Draw high scores title
	std::ostringstream ost;
	ost <<"High scores for "
	    <<last_window_size_.x
	    <<'×'
	    <<last_window_size_.y
	    <<'@'
	    <<Config::Instance().RefreshRate()
	    <<" window";
	X11::Inst().DrawString(pos, ost.str().c_str());
	pos.y += LineHeight();
	ost.str(std::string(ost.str().size(), '¯'));
	X11::Inst().DrawString(pos, ost.str().c_str());
	pos.y += LineHeight();

	// get high scores for current window size
	const std::multiset<HighScore> *const high_scores (HighScores::Instance().Get(last_window_size_, Config::Instance().RefreshRate()));
	if (!high_scores) {
		score_lines_.clear();
		ost.str("None.");
		X11::Inst().DrawString(pos, ost.str().c_str());
		return;
	}
	// Display high scores
	// The first line is always displayed
	// The best player is always displayed (on last line if necessary).
	int rank (0);
	size_t line (0);
	int last_score (-1);
	const std::string player_name (Config::Instance().GetPlayerName());
	bool look_for_player (false);
	bool player_displayed (false);
	for (std::multiset<HighScore>::const_reverse_iterator it (high_scores->rbegin());
	     (can_scroll_ = it != high_scores->rend()) &&
	     (look_for_player || pos.y < last_window_size_.y - LineHeight());
	     ++it) {
		++rank;
		if ((rank > scroll_scores_ && !look_for_player) ||
		    (look_for_player && it->Name() == player_name)) {
			// Construct this line
			ost.str("");
			if (it->Value() != last_score) {
				last_score = it->Value();
				ost << std::setfill(' ') << std::setw(2) << rank << ". ";
			} else {
				ost << "    ";
			}
			char score_date[20];
			const time_t score_date_tm = it->Date();
			
			strftime(score_date, sizeof score_date, "%x", localtime(&score_date_tm));
			// Null score date means no date recorded -> deplace date by spaces.
			if (it->Date() == 0) {
				for (int i = 0; score_date[i] != '\0'; ++i) {
					score_date[i] = ' ';
				}
			}
			ost << std::setfill(' ') << std::setw(6) << last_score
			    << "   " << score_date << ' ' << it->Name();
			// Undraw old line if is different
			const std::string score_line (ost.str());
			if (line == score_lines_.size()) score_lines_.push_back(score_line);
			else if (score_lines_[line] != score_line) {
				X11::Inst().SetForeground(X11::Inst().GetBlack());
				X11::Inst().DrawString(pos, score_lines_[line].c_str());
				score_lines_[line] = score_line;
			}
			// text color with special color for current player
			if (it->Name() == player_name) {
				player_displayed = true;
				if (color.green) color.green += (65535 - color.green) / 2;
			}
			if (color.red >= 1024) color.red -= 1024;
			X11::Inst().AllocColorAlways(&color);
			X11::Inst().SetForeground(color.pixel);
			if (it->Name() == player_name) {
				if (color.green) color.green -= 65535 - color.green;
			}
			X11::Inst().DrawString(pos, score_line.c_str());
			++line;
			pos.y += LineHeight();
			look_for_player = !player_displayed && pos.y >= last_window_size_.y - 2 * LineHeight();
		}
	}
}
