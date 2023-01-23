#include "config.h"
#include "gfxinterface.h"
#include "instance.h"
#include <pwd.h>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>


namespace {

std::string GetUserFullName()
{
	const passwd *const pwd (getpwuid(getuid()));
	const char * gecos (pwd->pw_gecos);
	if (!gecos || !gecos[0]) return pwd->pw_name;
	while (*gecos && *gecos != ',') ++gecos;
	return std::string(pwd->pw_gecos, gecos - pwd->pw_gecos);
}


std::string PlayerName()
{
	const char *const env_name (std::getenv("XGAL_PSEUDO"));
	return env_name ? env_name : GetUserFullName();
}


#define TO_STRING(s) #s
#define MAKE_STRING(s) TO_STRING(s)

#ifndef HIGH_SCORES_FILE
	#define HIGH_SCORES_FILE .xgalaga++.scores
#endif

// If absolute path, return as-is, else prefix with home dir.
std::string ScoreFileName()
{
	static const char scores_file_name[] = MAKE_STRING(HIGH_SCORES_FILE);
	if (scores_file_name[0] != '/') {
		const passwd *const pwd (getpwuid(getuid()));
		if (pwd->pw_dir) return std::string(pwd->pw_dir) + '/' + scores_file_name;
	}
	return scores_file_name;
}

}



/*
 * Config
 */

Config * Config::singleton_ (0);


Config & Config::Instance()
{
	if (!singleton_) {
		singleton_ = new Config;
		InstancesManager::Instance().Push(DestroyInstance);
	}
	return *singleton_;
}


Config::Config()
: details_level_  (max_details)
, refresh_rate_   (50)
, player_name_    (PlayerName())
, score_file_name_(ScoreFileName())
{
}


void Config::AddDetailsLevel(int i) {
	if (details_level_ + i >= min_details &&
	    details_level_ + i <= max_details) {
		details_level_ = details_level_ + i;
	}
}	


int Config::NextRefreshRate(void) const {
	return refresh_rate_ >= 120 ? 50 : refresh_rate_ + 5;
}


/*
 *
 */

void SetStandardWindowSize(unsigned win_size)
{
	static const unsigned widths[]  = { 640, 800, 1024, 1280, 1600 };
	static const unsigned heights[] = { 480, 600,  768, 1024, 1200 };
	if (win_size > 0 && win_size <= sizeof widths / sizeof widths[0]) {
		--win_size;
		X11::Inst().ResizeWindow(widths[win_size], heights[win_size]);
		X11::Inst().ClearWindow();
	}
}
