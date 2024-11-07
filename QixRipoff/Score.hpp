#pragma once
#include "toolbox/toolbox.hpp"

/// Mycelium
struct HighScore {
	std::string name;
	int score;

	// This exploded in the weirdest way possible, out it goes
	//	bool operator<(const HighScore& _a);
};

class Score {
private:
	int score;
	inline static sf::Text txtDisplay;
	inline static sf::Font txtFont;

	static void printHighscores();
	static void sortHighscores();
public:
	inline static std::vector<struct HighScore> highscores;
	inline static int enterLeaderboard;

	static void preinit();
	Score();

	void init();
	void render(class Window& _w, sf::Vector2u _pos);

	void addScore(const int _val) { this->score += _val; }
	int getScore() const { return this->score; }

	static void saveHighScores();
	static void loadHighScores();
	static void loadDefaultHighScores();
	static void addHighScore(std::string _name, int _score);
};