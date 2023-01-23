#include "highscore.h"
#include "instance.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>

using std::string;

/*
 *  HighScores
 */

HighScores * HighScores::singleton_ (0);


HighScores & HighScores::Instance() {
	if (!singleton_) {
		singleton_ = new HighScores;
		InstancesManager::Instance().Push(DestroyInstance);
	}
	return *singleton_;
}


void HighScores::Update()
{
	const std::string score_file_name (Config::Instance().GetScoreFileName());
	PosixBuf filebuf (score_file_name, O_RDWR | O_CREAT, 0660);
	if (filebuf.FD() < 0)
		throw std::runtime_error ("Cannot open high scores file '"+score_file_name+"'!");
	if (filebuf.Lock(last_score_ != -1 ? F_WRLCK : F_RDLCK) == -1)
		throw std::runtime_error ("Cannot lock high scores file '"+score_file_name+"'!");
	std::iostream file (&filebuf);
	Load(file);
	file.clear();
	if (last_score_ != -1) {
		high_scores_[last_rate_][last_size_].insert(HighScore(last_score_));
		last_score_ = -1;
		if (filebuf.Truncate() != 0)
			throw std::runtime_error ("Cannot update high scores file '"+score_file_name+"'!");
		file.seekg(0);
		Save(file);
	}
}


const std::multiset<HighScore> * HighScores::Get(Coord window_size, int refresh_rate) const
{
	const MapRateCoordScore::const_iterator it1 (high_scores_.find(refresh_rate));
	if (it1 == high_scores_.end()) return 0;
	const MapCoordScore::const_iterator it2 (it1->second.find(window_size));
	return it2 == it1->second.end() ? 0 : &(it2->second);
}


void HighScores::Load(std::istream & scores_file)
{
	high_scores_.clear();
	int score;
	Coord window_size;
	string name;
	std::time_t score_date;
	int refresh_rate;

	while (scores_file.peek() != EOF) {
		score_date = 0;
		refresh_rate = 50;

		if (scores_file.peek() == '@') {
			scores_file.ignore();
			if (!(scores_file >> refresh_rate >> score_date >> score >> window_size.x >> window_size.y && std::getline(scores_file, name))) {
				break;
			}
		}
		else if (scores_file.peek() == 'T') {
			scores_file.ignore();
			if (!(scores_file >> score_date >> score >> window_size.x >> window_size.y && std::getline(scores_file, name))) {
				break;
			}
		}
		else {
			if (!(scores_file >> score >> window_size.x >> window_size.y && std::getline(scores_file, name))) {
				break;
			}
		}

		if (!name.empty()) {
			name.erase(0, 1);
		}

		high_scores_[refresh_rate][window_size].insert(HighScore(score, name, score_date));
	}

	if (!scores_file.eof())
		throw std::runtime_error ("Error while reading high scores file '"+Config::Instance().GetScoreFileName()+"'!");
}


void HighScores::Save(std::ostream & scores_file) const
{
	for (MapRateCoordScore::const_iterator rateit (high_scores_.begin());
	     rateit != high_scores_.end(); ++rateit) {
		for (MapCoordScore::const_iterator coordit (rateit->second.begin());
			 coordit != rateit->second.end(); ++coordit) {
			for (std::multiset<HighScore>::const_iterator setit (coordit->second.begin());
				 setit != coordit->second.end(); ++setit) {
				scores_file << '@'
							<< rateit->first << ' '
							<< setit->Date() << ' '
							<< setit->Value() << ' '
							<< coordit->first.x << ' '
							<< coordit->first.y << ' '
							<< setit->Name() << '\n';
				if (!scores_file.good()) {
					throw std::runtime_error ("Error while saving high scores file '"+Config::Instance().GetScoreFileName()+"'!");
				}
			}
		}
	}
}
