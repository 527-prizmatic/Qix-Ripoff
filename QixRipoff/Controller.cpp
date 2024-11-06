#include "Controller.hpp"
#include "Window.hpp"
#include <Windows.h>

int buttoncount = 14;
int playernber;

// This define makes your program compile faster by excluding things we are not using
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#if (_WIN32_WINNT >= 0x0602 )
#include <XInput.h>
#pragma comment(lib,"xinput.lib")
#else
#include <XInput.h>
#pragma comment(lib,"xinput9_1_0.lib")
#endif

namespace ctrl {

	ControllerKey::ControllerKey(std::string _str, GamepadXBOX _key, Stick _stick)
	{
		this->id = _str;
		this->key = _key;
		this->stick = _stick;
		this->state = IDLE;
	}
	Controller::Controller()
	{
		this->window = nullptr;
	}
	Controller::Controller(Window* _window)
	{
		this->window = _window;
	}
	Controller& Controller::addKey(std::string _str, GamepadXBOX _key, Stick _stick)
	{
		this->keyReg.push_back(ControllerKey(_str, _key, _stick));
		return *this;
	}
	Controller& Controller::setKey(std::string _str, GamepadXBOX _key, Stick _stick)
	{
		for (ControllerKey& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				k.setKey(_key);
				k.setStick(_stick);
				return *this;
			}
		}
		return *this;
	}
	void Controller::GamepadDetection()
	{
		sf::Joystick::update();
		playernber = 0;
		for (unsigned int i = 0; i < 8; i++)
		{
			if (playernber >= 1) break;
			if (sf::Joystick::isConnected(i) == true)
				playernber++;
		}
	}
}