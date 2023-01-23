#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include "config.h"
#include "gfxinterface.h"
#include "posix_stream.h"
#include <iosfwd>
#include <map>
#include <set>
#include <string>
#include <ctime>


class HighScore {
	int score_;
	std::string name_;
	std::time_t date_;

	friend class HighScores;
	HighScore(int score,
	          const std::string & name = Config::Instance().GetPlayerName(),
			  std::time_t date = std::time(0))
		: score_(score), name_(name), date_(date) {}
public:
	int Value() const { return score_; }
	std::string Name() const { return name_; }
	std::time_t Date() const { return date_; }
};


inline bool operator<(const HighScore & lhs, const HighScore & rhs)
	{ return lhs.Value() < rhs.Value(); }


class HighScores {
	static HighScores * singleton_;

	typedef std::map<Coord, std::multiset<HighScore> > MapCoordScore;
	typedef std::map<int, MapCoordScore> MapRateCoordScore;
	MapRateCoordScore high_scores_;
	int last_score_;
	Coord last_size_;
	int last_rate_;

	HighScores() : last_score_(-1) {}
public:
	static HighScores & Instance();
	static void DestroyInstance() { delete singleton_; singleton_ = 0; }

	void Add(int score, Coord window_size, int refresh_rate) {
		last_score_ = score;
		last_size_ = window_size;
		last_rate_ = refresh_rate;
	}
	void Update();
	const std::multiset<HighScore> * Get(Coord window_size, int refresh_rate) const;
private:
	void Load(std::istream &);
	void Save(std::ostream &) const;
};


#endif
