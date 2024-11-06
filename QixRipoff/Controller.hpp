#pragma once
#include "toolbox/toolbox.hpp"
#include <SFML/Window/Joystick.hpp>

typedef enum gamepadXBOX gamepadXBOX;
enum GamepadXBOX {
	DPAD_UP = 0x0001,
	DPAD_DOWN = 0x0002,
	DPAD_LEFT = 0x0004,
	DPAD_RIGHT = 0x0008,
	START = 0x0010,
	BACK = 0x0020,
	LEFT_THUMB = 0x0040,
	RIGHT_THUMB = 0x0080,
	LB = 0x0100,
	RB = 0x0200,
	A = 0x1000,
	B = 0x2000,
	X = 0x4000,
	Y = 0x8000
};

typedef enum stick stick;
enum Stick {
	STICKL,
	STICKR,
	DPAD
};

class Window;

namespace ctrl {
	class ControllerKey
	{
	private : 
		std::string id;
		GamepadXBOX key;
		Stick stick;
		ButtonState state;
	public : 
		ControllerKey(std::string _str, GamepadXBOX _key, Stick _stick);
		const std::string getId() { return this->id; }
		const GamepadXBOX getKey() { return this->key; }
		const Stick getStick() { return this->stick; }
		const ButtonState getState() { return this->state; }
		void setKey(GamepadXBOX _key) { this->key = _key; }
		void setStick(Stick _stick) { this->stick = _stick; }
		void setState(ButtonState _state) { this->state = _state; }
	};
	class Controller
	{
	private : 
		int keyCtrlCount;
		Window* window;
		std::vector<ControllerKey> keyReg;
		sf::Vector2f stickL;
		sf::Vector2f stickR;
	public: 
		Controller();
		Controller(Window* _window);
		void setWindow(Window* _window) { this->window = _window; }
		Controller& addKey(std::string _str, GamepadXBOX _key, Stick _stick);
		Controller& setKey(std::string _str, GamepadXBOX _key, Stick _stick);
		void GamepadDetection();
		void update();
		bool idle(std::string _str);
		bool pressed(std::string _str);
		bool held(std::string _str);
		bool released(std::string _str);
	};
}

