#pragma once
#include "toolbox/toolbox.hpp"
#include <SFML/Window/Joystick.hpp>

typedef enum GamepadXBOX GamepadXBOX;
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

typedef enum Stick Stick;
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
		ButtonState state;
	public : 
		ControllerKey(std::string _str, GamepadXBOX _key);
		const std::string getId() { return this->id; }
		const GamepadXBOX getKey() { return this->key; }
		const ButtonState getState() { return this->state; }
		void setKey(GamepadXBOX _key) { this->key = _key; }
		void setState(ButtonState _state) { this->state = _state; }
	};
	class Controller
	{
	private : 
		int keyCtrlCount;
		class Window* window;
		std::vector<ControllerKey> keyReg;
		sf::Vector2f stickL;
		sf::Vector2f stickR;
		sf::Vector2f cross;
		float TriggerL;
		float TriggerR;
		int Bouton[14];
	public: 
		Controller();
		Controller(Window* _window);
		void setWindow(Window* _window) { this->window = _window; }
		Controller& addKey(std::string _str, GamepadXBOX _key);
		Controller& setKey(std::string _str, GamepadXBOX _key);
		void GamepadDetection();
		void GamepadManager(int _joystickId);
		int Gamepad_isButtonPressed(unsigned int _joystickId, GamepadXBOX _button);
		void update();
		bool idle(std::string _str);
		bool pressed(std::string _str);
		bool held(std::string _str);
		bool released(std::string _str);
	};
}

