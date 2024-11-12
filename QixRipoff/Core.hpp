#pragma once
#include <unordered_map>
#include "toolbox/toolbox.hpp"
#include "Window.hpp"
#include "controls/Mouse.hpp"
#include "controls/Keyboard.hpp"
#include "Controller.hpp"
#include "states/State.hpp"
#include "Score.hpp"

typedef enum GameState GameState;
enum GameState {
	NONE,
	ALL,
	INTRO,
	MENU,
	GAME,
	LEADERBOARD,
	END
};

class Core {
private:
	std::unordered_map<enum GameState, states::State*> stateReg;
	enum GameState state;
	bool initPending;
	Window window;

	bool stateChangePending;
	enum GameState nextState;
	ctrl::Mouse mouse;
	ctrl::Keyboard kb;
	ctrl::Controller controller;
	Score scores;

	void initState();
public:
	Core();

	void init();
	void update();
	void render();
	void unload();

	Core& registerState(GameState _id, states::State* _state);
	GameState getState() { return this->state; }
	void requestStateChange(GameState _s);
	void changeState();

	bool windowIsOpen() { return this->window.isOpen(); }
	Window& getWindow() { return this->window; }
	ctrl::Mouse& getMouse() { return this->mouse; }
	ctrl::Keyboard& getKeyboard() { return this->kb; }
	ctrl::Controller& getController() { return this->controller; }
	Score& getScores() { return this->scores; }
	void beginRendering();
	void endRendering();
};

