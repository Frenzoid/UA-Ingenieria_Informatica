#include "config.h"
#include "constants.h"
#include "gfxinterface.h"
#include "highscore.h"
#include "input.h"
#include "instance.h"
#include "managers.h"
#include "menu.h"
#include "score.h"
#include "stars.h"
#include "time_util.h"
#include "xpms.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>


namespace Data {

// The following arrays are arrival trajectories defined with relative
// coordinates.
// RCEnd is the end marker.

const RCoord hang[] = {
	RCoord(512,-20), RCoord(512,612), RCoord(496,662), RCoord(454,704),
	RCoord(414,716), RCoord(368,704), RCoord(330,662), RCoord(318,612),
	RCoord(330,556), RCoord(512,260),
	RCEnd
};
const RCoord infinity[] = {
	RCoord(-20,800),
	RCoord(460+300,544-200), RCoord(512+300,530-200),
	RCoord(560+300,544-200), RCoord(592+300,588-200),
	RCoord(598+300,618-200), RCoord(592+300,648-200),
	RCoord(560+300,690-200), RCoord(512+300,702-200),
	RCoord(512-300,702-200), RCoord(462-300,690-200),
	RCoord(430-300,648-200), RCoord(422-300,618-200),
	RCoord(428-300,588-200), RCoord(460-300,544-200),
	RCEnd
};
const RCoord v[] = {
	RCoord(-20,312), RCoord(350,550), RCoord(700,550), RCoord(800,500),
	RCEnd
};
const RCoord u[] = {
	RCoord(256,-20), RCoord(256,600), RCoord(768,600), RCoord(768,200),
	RCEnd
};
const RCoord loop[] = {
	RCoord(-20,430),
	RCoord(512,430), RCoord(560,444), RCoord(592,488), RCoord(598,518),
	RCoord(592,548), RCoord(560,590), RCoord(512,602), RCoord(462,590),
	RCoord(430,548), RCoord(422,518), RCoord(428,488), RCoord(460,444),
	RCoord(512,430), RCoord(560,444), RCoord(592,488), RCoord(598,518),
	RCoord(592,548), RCoord(560,590), RCoord(512,602), RCoord(462,590),
	RCoord(430,548), RCoord(422,518), RCoord(428,488), RCoord(460,444),
	RCEnd
};
const RCoord left[] =  { RCoord(-20,512),     RCoord(512,512), RCEnd };
const RCoord sine[] = {
	RCoord(-20,586), RCoord(0,566),   RCoord(20,540),  RCoord(66,524),
	RCoord(124,548), RCoord(152,588), RCoord(158,634), RCoord(182,676),
	RCoord(244,700), RCoord(302,676), RCoord(328,634), RCoord(338,588),
	RCoord(364,548), RCoord(422,524), RCoord(482,548), RCoord(506,588),
	RCEnd
};
const RCoord t_diag[] = { RCoord(-20,-20),     RCoord(512,700), RCEnd };
const RCoord b_diag[] = { RCoord(-20,1024+20), RCoord(512,316), RCEnd };
const RCoord b_zz[] = {
	RCoord(-20,1000), RCoord(100,1000), RCoord(0,900), RCoord(100,900),
	RCoord(0,800), RCoord(100,800), RCoord(0,700), RCoord(100,700),
	RCoord(0,600), RCoord(100,600), RCoord(0,500), RCoord(100,500),
	RCoord(0,400), RCoord(100,400),
	RCEnd
};
const RCoord t_zz[] = {
	RCoord(-20,100), RCoord(100,100), RCoord(0,200), RCoord(100,200),
	RCoord(0,300),   RCoord(100,300), RCoord(0,400), RCoord(100,400),
	RCoord(0,500),   RCoord(100,500), RCoord(0,600), RCoord(100,600),
	RCoord(0,700),   RCoord(100,700),
	RCEnd
};
const RCoord t_circ[] = {
	RCoord(20,-20), RCoord(20,194), RCoord(22,240), RCoord(30,280),
	RCoord(38,320), RCoord(52,360), RCoord(66,402), RCoord(88,446),
	RCoord(112,490), RCoord(144,532), RCoord(172,566), RCoord(212,604),
	RCoord(246,630), RCoord(292,660), RCoord(334,680), RCoord(394,700),
	RCoord(436,710), RCoord(512,716), RCoord(1024-436,710),
	RCoord(1024-394,700), RCoord(1024-334,680), RCoord(1024-292,660),
	RCoord(1024-246,630), RCoord(1024-212,604), RCoord(1024-172,566),
	RCoord(1024-144,532), RCoord(1024-112,490), RCoord(1024-88,446),
	RCoord(1024-66,402), RCoord(1024-52,360), RCoord(1024-38,320),
	RCoord(1024-30,280), RCoord(1024-22,240), RCoord(1024-20,194),
	RCEnd
};
const RCoord boing[] = {
	RCoord(24,1024+20), RCoord(24,796), RCoord(30,716), RCoord(40,644),
	RCoord(50,608), RCoord(60,576), RCoord(70,538), RCoord(80,516),
	RCoord(90,496), RCoord(100,476), RCoord(110,464), RCoord(120,446),
	RCoord(130,426), RCoord(140,420), RCoord(150,406), RCoord(160,390),
	RCoord(170,386), RCoord(180,376), RCoord(190,366), RCoord(200,362),
	RCoord(210,356), RCoord(220,350), RCoord(230,346), RCoord(240,344),
	RCoord(250,340), RCoord(260,339), RCoord(278,338),
	RCoord(2*278-260,339), RCoord(2*278-250,340), RCoord(2*278-240,344),
	RCoord(2*278-230,346), RCoord(2*278-220,350), RCoord(2*278-210,356),
	RCoord(2*278-200,362), RCoord(2*278-190,366), RCoord(2*278-180,376),
	RCoord(2*278-170,386), RCoord(2*278-160,390), RCoord(2*278-150,406),
	RCoord(2*278-140,420), RCoord(2*278-130,426), RCoord(2*278-120,446),
	RCoord(2*278-110,464), RCoord(2*278-100,476), RCoord(2*278-90,496),
	RCoord(2*278-80,516), RCoord(2*278-70,538), RCoord(2*278-60,576),
	RCoord(2*278-50,608), RCoord(2*278-40,644), RCoord(2*278-30,716),
	RCoord(2*278-24, 796),
	RCEnd
};
const RCoord drop128[] = { RCoord(128,-20), RCoord(128,700), RCEnd };
const RCoord drop256[] = { RCoord(256,-20), RCoord(256,700), RCEnd };
const RCoord drop384[] = { RCoord(384,-20), RCoord(384,700), RCEnd };
const RCoord drop512[] = { RCoord(512,-20), RCoord(512,700), RCEnd };
const RCoord drop640[] = { RCoord(640,-20), RCoord(640,700), RCEnd };
const RCoord drop768[] = { RCoord(768,-20), RCoord(768,700), RCEnd };
const RCoord drop896[] = { RCoord(896,-20), RCoord(896,700), RCEnd };

// The following arrays fully define the game levels with the
// following parameters:
// - delay in frames before aliens convoy creation
// - XPM data to draw the alien
// - percentage of window width taken by the aliens convoy
// - aliens convoy trajectory 
// - boolean, true iff the convoy is mirrored
// - boolean, true iff the convoy is made of two mirrored half-convoys

const ConvoyData cd1[] = {
	{  0, alien1_xpm,  50, hang, false, true },
	{100, alien1_xpm,  50, hang, false, true },
	{100, alien1_xpm,  50, hang, false, true },
	{100, alien1_xpm,  50, hang, false, true },
	{100, alien1_xpm,  30, hang, false, true },
	{ 10, alien13_xpm, 15, hang, false, true },
	{0,0,0,0,false,false}
};
const ConvoyData cd2[] = {
	{200, alien2_xpm,  50, v,    false, false },
	{150, alien2_xpm,  50, v,    true,  false },
	{150, alien2_xpm,  50, v,    false, false },
	{100, alien2_xpm,  50, v,    true,  false },
	{100, alien2_xpm,  30, hang, false, true },
	{ 10, alien13_xpm, 15, hang, false, true },
	{0,0,0,0,false,false}
};
const ConvoyData cd3[] = {
	{200, alien3_xpm, 50, t_diag, false, false },
	{200, alien3_xpm, 50, t_diag, true,  false },
	{200, alien3_xpm, 50, t_diag, false, true },
	{10,  alien3_xpm, 50, t_diag, true,  true },
	{0,0,0,0,false,false}
};
const ConvoyData cd4[] = {
	{200, alien4_xpm,  50, u, false, true },
	{170, alien4_xpm,  50, u, false, true },
	{170, alien4_xpm,  50, u, false, true },
	{170, alien4_xpm,  50, u, false, true },
	{150, alien4_xpm,  30, v, false, false },
	{ 10, alien13_xpm, 15, v, false, false },
	{0,0,0,0,false,false}
};
const ConvoyData cd5[] = {
	{200, alien5_xpm, 50, loop,     false, false },
	{ 25, alien5_xpm, 50, loop,     true,  false },
	{150, alien5_xpm, 50, b_diag,   false, false },
	{150, alien5_xpm, 50, b_diag,   true,  false },
	{150, alien5_xpm, 50, loop,     false, false },
	{0,0,0,0,false,false}
};
const ConvoyData cd6[] = {
	{200, alien6_xpm,  50, hang,     false, true },
	{150, alien6_xpm,  50, infinity, false, true },
	{150, alien6_xpm,  50, infinity, true,  false },
	{100, alien6_xpm,  30, infinity, false, false },
	{100, alien6_xpm,  50, infinity, true,  false },
	{150, alien13_xpm, 15, b_diag,   true,  false },
	{0,0,0,0,false,false}
};
const ConvoyData cd7[] = {
	{200, alien7_xpm, 50, b_zz, false, true },
	{150, alien7_xpm, 50, t_zz, false, true },
	{100, alien7_xpm, 50, b_zz, false, true },
	{ 50, alien7_xpm, 50, t_zz, false, true },
	{ 10, alien7_xpm, 50, t_zz, false, true },
	{0,0,0,0,false,false}
};
const ConvoyData cd8[] = {
	{200, alien8_xpm, 50, sine,    false, false },
	{  0, alien8_xpm, 50, sine,    true,  true },
	{ 50, alien8_xpm, 25, drop128, false, true },
	{  5, alien8_xpm, 25, drop256, false, true },
	{  5, alien8_xpm, 25, drop384, false, true },
	{  5, alien8_xpm, 25, drop512, false, true },
	{  5, alien8_xpm, 25, drop640, false, true },
	{  5, alien8_xpm, 25, drop768, false, true },
	{0,0,0,0,false,false}
};
const ConvoyData cd9[] = {
	{200, alien9_xpm, 10, t_circ, false, false },
	{ 50, alien9_xpm, 20, t_circ, true,  false },
	{ 50, alien9_xpm, 30, t_circ, false, false },
	{ 50, alien9_xpm, 40, t_circ, true,  false },
	{ 50, alien9_xpm, 50, t_circ, false, true },
	{ 50, alien9_xpm, 50, t_circ, true,  true },
	{ 50, alien9_xpm, 40, t_circ, false, false },
	{ 50, alien9_xpm, 30, t_circ, true,  false },
	{ 50, alien9_xpm, 20, t_circ, false, false },
	{ 50, alien9_xpm, 10, t_circ, true,  false },
	{0,0,0,0,false,false}
};
const ConvoyData cd10[] = {
	{200, alien10_xpm, 50, boing, false, false },
	{50,  alien10_xpm, 50, boing, true,  false },
	{10,  alien10_xpm, 50, boing, false, true },
	{10,  alien10_xpm, 50, boing, false, true },
	{10,  alien10_xpm, 50, boing, false, true },
	{10,  alien10_xpm, 50, boing, false, true },
	{10,  alien10_xpm, 50, boing, false, true },
	{10,  alien10_xpm, 50, boing, false, true },
	{0,0,0,0,false,false}
};
const ConvoyData cd11[] = {
	{200, alien11_xpm, 50, sine, false, true },
	{25,  alien11_xpm, 50, sine, false, true },
	{25,  alien11_xpm, 50, sine, false, true },
	{25,  alien11_xpm, 50, sine, false, true },
	{0,0,0,0,false,false}
};
const ConvoyData cd12[] = {
	{200, alien12_xpm, 13, drop128, false, false },
	{0, alien12_xpm, 13, drop896, false, false },
	{0, alien12_xpm, 13, drop256, false, false },
	{0, alien12_xpm, 13, drop768, false, false },
	{0, alien12_xpm, 13, drop384, false, false },
	{0, alien12_xpm, 13, drop640, false, false },
	{0, alien13_xpm, 25, drop512, false, false },
	{0,0,0,0,false,false}
};
const ConvoyData cd13[] = {
	{100, alien14_xpm, 50, v, false, true },
	{0,   alien1_xpm,  50, v, false, true },
	{0,   alien2_xpm,  50, v, false, true },
	{0,   alien3_xpm,  50, v, false, true },
	{0,   alien4_xpm,  50, v, false, true },
	{0,   alien5_xpm,  50, v, false, true },
	{0,   alien6_xpm,  50, v, false, true },
	{0,   alien7_xpm,  50, v, false, true },
	{0,   alien8_xpm,  50, v, false, true },
	{0,   alien9_xpm,  50, v, false, true },
	{0,0,0,0,false,false}
};


// Game levels
const ConvoyData *const levels[] = {
	cd1, cd2, cd3, cd4, cd5, cd6, cd7, cd8, cd9, cd10, cd11, cd12, cd13
};

} // namespace Data



/*
 *  Main functions
 */

AliensManager * NewLevel(BulletsManager * bombs_manager,
                         BulletsManager * bullets_manager,
                         BonusManager * bonus_manager,
                         ExplosionsManager * explosions_manager)
{
	const size_t nb_levels (sizeof Data::levels / sizeof Data::levels[0]);
	const size_t data_number ((Score::Instance().Level() - 1) % nb_levels);
	return new AliensManager (bombs_manager, bullets_manager,
	                          bonus_manager, explosions_manager,
	                          Score::Instance().Level(),
	                          Data::levels[data_number],
	                          nb_levels);
}


void Play()
{
	X11::Inst().ClearWindow();
	Score::Instance().ReInit();

	Input input;
	BulletsManager bullets, bombs;
	BonusManager bonuses;
	ExplosionsManager explosions;
	std::auto_ptr<AliensManager> aliens (NewLevel(&bombs, &bullets, &bonuses, &explosions));
	Player player (&bullets, &bombs, &bonuses, &explosions, Score::Instance().Height() + 1);
	Score::Instance().SetShield(player.Shield());
	int fast_star_scrolling_time (0);
	bool cheated (false);
	bool window_resized (false);
	bool rate_changed (false);
	Coord last_window_size (X11::Inst().WindowWidth(), X11::Inst().WindowHeight());
	double frame_time (0);
	
	for (;;) {
		input.Update();
		if (input.Quit()) break;
		if (!input.Pause()) {
			Config::Instance().AddDetailsLevel(input.Details());
			
			if (input.IncRefreshRate()) {
				Config::Instance().SetNextRefreshRate();
				rate_changed = true;
			}
			
			SetStandardWindowSize(input.WindowSize());
			X11::Inst().GetWindowAttributes();
			if (last_window_size != Coord(X11::Inst().WindowWidth(), X11::Inst().WindowHeight())) {
				last_window_size = Coord(X11::Inst().WindowWidth(), X11::Inst().WindowHeight());
				window_resized = true;
			}
		
			const int old_score (Score::Instance().Value());
			Score::Instance().Add(aliens->DoBulletsCollisions());
			if (old_score % 1000 > Score::Instance().Value() % 1000) {
				player.ExtraShield();
			}
			player.DoBombsCollisions();
			player.DoBonusCollisions();
			if (input.Cheat()) {
				cheated = true;
				player.ExtraFire();
				player.ExtraShield();
			}

			Score::Instance().SetShield(player.Shield());
			if (player.Shield() < 0) {
				if (!cheated && !window_resized && !rate_changed) {
					HighScores::Instance().Add(Score::Instance().Value(), last_window_size, Config::Instance().RefreshRate());
				}
				break;
			}

			if (aliens->Finished()) {
				Score::Instance().IncLevel();
				std::auto_ptr<AliensManager> n (NewLevel(&bombs, &bullets, &bonuses, &explosions));
				aliens = n;
				fast_star_scrolling_time = 100;
			}

			StarsFields::Instance().Scroll();
			if (fast_star_scrolling_time > 0) {
				--fast_star_scrolling_time;
				if (fast_star_scrolling_time == 0) Score::Instance().EraseLevel();
				StarsFields::Instance().Scroll();
				StarsFields::Instance().Scroll();
				if (fast_star_scrolling_time > 0) Score::Instance().ShowLevel();
			}

			aliens->Move();
			bonuses.Move();
			player.Move(input.Move());
			bullets.Move();
			bombs.Move();
			aliens->Fire();
			if (input.Fire()) player.Fire();
			explosions.Move();
			Score::Instance().Refresh();
		}
		X11::Inst().Sync(False);
		frame_time = SleepTimeInterval(frame_time, 1.0 / Config::Instance().RefreshRate());
	}
}


void MainLoop()
{
	X11::CreateInstance();
	X11::Inst().SetWindowTitle("XGalaga++");
	X11::Inst().SetInvisibleCursor();
	while (StartMenu::Instance().Display()) {
		Play();
	}
}


int main()
{
	int code (0);
	try {
		MainLoop();
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
		code = 1;
	}
	catch (...) {
		std::cerr << "Unknown exception." << std::endl;
		code = 1;
	}
	InstancesManager::DestroyInstance();
	return code;
}
