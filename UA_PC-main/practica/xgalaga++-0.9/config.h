#ifndef CONFIG_H
#define CONFIG_H

#include <string>


// Store configuration
class Config {
	static Config * singleton_;

	enum { min_details = 0, max_details = 4 };
	int details_level_;
	int refresh_rate_;
	const std::string player_name_;
	const std::string score_file_name_;

	Config();
	Config(const Config&); // no copy
	Config & operator=(const Config&); // no copy
public:
	static Config & Instance();
	static void DestroyInstance() { delete singleton_; singleton_ = 0; }

	void AddDetailsLevel(int);
	int ScaleDetails(int val) const
		{ return val * details_level_ / max_details; }
	int MaxDetails() const { return max_details; }
	int RefreshRate(void) const { return refresh_rate_; }
	int NextRefreshRate(void) const;
	void SetNextRefreshRate(void) { refresh_rate_ = NextRefreshRate(); }
	const std::string & GetPlayerName() const { return player_name_; }
	const std::string & GetScoreFileName() const { return score_file_name_; }
};


// Resize window to standard size, 0 has no effect.
void SetStandardWindowSize(unsigned win_size);

#endif
