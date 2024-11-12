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

	ControllerKey::ControllerKey(std::string _str, GamepadXBOX _key)
	{
		this->id = _str;
		this->key = _key;
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
	Controller& Controller::addKey(std::string _str, GamepadXBOX _key)
	{
		this->keyReg.push_back(ControllerKey(_str, _key));
		return *this;
	}
	Controller& Controller::setKey(std::string _str, GamepadXBOX _key)
	{
		for (ControllerKey& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				k.setKey(_key);
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
	void Controller::GamepadManager(int _joystickId)
	{
		if (this->window->getEvent().type == sf::Event::JoystickConnected) {
			// printf("Gamepad is Connected id %d\n", event.joystickConnect.joystickId);
			GamepadDetection();
		}
		if (this->window->hasFocus()) {
			if (this->window->getEvent().joystickButton.joystickId == _joystickId && this->window->hasFocus()) {
				XINPUT_STATE state;
				ZeroMemory(&state, sizeof(XINPUT_STATE));

				XInputGetState(_joystickId, &state);

				if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
					(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
						state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) {

					state.Gamepad.sThumbLX = 0;
					state.Gamepad.sThumbLY = 0;

				}

				if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
					(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
						state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) {

					state.Gamepad.sThumbRX = 0;
					state.Gamepad.sThumbRY = 0;

				}

				this[_joystickId].stickL.x = (float)(state.Gamepad.sThumbLX / 327);
				this[_joystickId].stickL.y = (float)(state.Gamepad.sThumbLY / 327);
				this[_joystickId].stickR.x = (float)(state.Gamepad.sThumbRX / 327);
				this[_joystickId].stickR.y = (float)(state.Gamepad.sThumbRY / 327);

				if ((state.Gamepad.wButtons & DPAD_RIGHT)) {
					this[_joystickId].cross.x = 100.f;
				}
				else if ((state.Gamepad.wButtons & DPAD_LEFT)) {
					this[_joystickId].cross.x = -100.f;
				}
				else {
					this[_joystickId].cross.x = 0.f;
				}

				if ((state.Gamepad.wButtons & DPAD_UP)) {
					this[_joystickId].cross.y = 100.f;
				}
				else if ((state.Gamepad.wButtons & DPAD_DOWN)) {
					this[_joystickId].cross.y = -100.f;
				}
				else {
					this[_joystickId].cross.y = 0.f;
				}

				this[_joystickId].TriggerL = (float)(state.Gamepad.bLeftTrigger) / 255;
				this[_joystickId].TriggerR = (float)(state.Gamepad.bRightTrigger) / 255;

				this[_joystickId].Bouton[0] = (state.Gamepad.wButtons & A);
				this[_joystickId].Bouton[1] = (state.Gamepad.wButtons & B);
				this[_joystickId].Bouton[2] = (state.Gamepad.wButtons & X);
				this[_joystickId].Bouton[3] = (state.Gamepad.wButtons & Y);
				this[_joystickId].Bouton[4] = (state.Gamepad.wButtons & LB);
				this[_joystickId].Bouton[5] = (state.Gamepad.wButtons & RB);
				this[_joystickId].Bouton[6] = (state.Gamepad.wButtons & START);
				this[_joystickId].Bouton[7] = (state.Gamepad.wButtons & BACK);
				this[_joystickId].Bouton[8] = (state.Gamepad.wButtons & LEFT_THUMB);
				this[_joystickId].Bouton[9] = (state.Gamepad.wButtons & RIGHT_THUMB);
				this[_joystickId].Bouton[10] = 0;
				this[_joystickId].Bouton[11] = 0;
				this[_joystickId].Bouton[12] = 0;
				this[_joystickId].Bouton[13] = 0;


			}
			else {
				this[_joystickId].stickL.x = 0.0f;
				this[_joystickId].stickL.y = 0.0f;
				this[_joystickId].stickR.y = 0.0f;
				this[_joystickId].stickR.x = 0.0f;
				this[_joystickId].cross.x = 0.0f;
				this[_joystickId].cross.y = 0.0f;
			}
		}
	}
	int Controller::Gamepad_isButtonPressed(unsigned int _joystickId, GamepadXBOX _button)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (this->window->hasFocus()) {
			XInputGetState(_joystickId, &state);
			if (state.Gamepad.wButtons & _button) {
				return (state.Gamepad.wButtons & _button);
			}
			else {
				return false;
			}
		}
	}
	void Controller::update()
	{
		for (ControllerKey& k : this->keyReg) {
			bool clicked = false; 
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));
			float x, y;
			if (this->window->hasFocus()) {
				clicked = Controller::Gamepad_isButtonPressed(1, k.getKey());
			}
			if (clicked) {
				if (k.getState() == IDLE) k.setState(CLICK);
				else k.setState(HOLD);
			}
			else {
				if (k.getState() == HOLD) k.setState(RELEASE);
				else k.setState(IDLE);
			}
		}
	}
	bool Controller::idle(std::string _str)
	{
		for (ControllerKey& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				return k.getState() == RELEASE || k.getState() == IDLE;
			}
		}
		return false;
	}
	bool Controller::pressed(std::string _str)
	{
		for (ControllerKey& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				return k.getState() == CLICK;
			}
		}
		return false;
	}
	bool Controller::held(std::string _str)
	{
		for (ControllerKey& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				return k.getState() == CLICK || k.getState() == HOLD;
			}
		}
		return false;
	}
	bool Controller::released(std::string _str)
	{
		for (ControllerKey& k : this->keyReg) {
			if (!k.getId().compare(_str)) {
				return k.getState() == RELEASE;
			}
		}
		return false;
	}
}