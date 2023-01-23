#ifndef INPUT_H
#define INPUT_H


class Input {
	bool quit_;
	int  move_;
	bool left_, right_, last_is_left_;
	int  vmove_;
	bool up_, down_, last_is_up_;
	bool fire_, firing_;
	bool start_;
	bool pause_;
	bool cheat_;
	bool highscores_;
	int  details_;
	int  window_size_;
	bool inc_refresh_rate_;
public:
	Input();
	void Update();
	bool Quit()           const { return quit_; }
	int  Move()           const { return move_; }
	int  VMove()          const { return vmove_; }
	bool Fire()           const { return fire_; }
	bool Start()          const { return start_; }
	bool Pause()          const { return pause_; }
	bool Cheat()          const { return cheat_; }
	bool HighScores()     const { return highscores_; }
	int  Details()        const { return details_; }
	int  WindowSize()     const { return window_size_; }
	bool IncRefreshRate() const { return inc_refresh_rate_; }
};


#endif
