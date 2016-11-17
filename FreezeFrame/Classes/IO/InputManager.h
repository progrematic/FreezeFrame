#ifndef FF_INPUTMANAGER
#define FF_INPUTMANAGER

#include <SFML/Graphics.hpp>
#include "../../Globals.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
using namespace sf;

class InputManager
{
public:
	enum InputID
	{
		A,
		B,
		X,
		Y,
		LB,
		RB,
		Back,
		Start,
		LS,
		RS,
		InputIDMax
	};

	enum AxisID
	{
		LHorizontal,
		LVertical,
		Triggers,
		RVertical,
		RHorizontal,
		HatHorizontal,
		HatVertical,
		AxisIDMax
	};

	static InputManager* GetInstance();

	InputManager();
	~InputManager();

	void PollEvent(Event e);
	void Update(float dt);
	void Draw(RenderWindow* window);

private:
	struct ButtonInput
	{
		ButtonInput() 
		{
			id = InputID::InputIDMax;
			keyboardMapping = -1;
			joystickMapping = -1;
			mouseMapping = -1;

			pressed = false;
			down = false;
			released = false;
		}

		string ToString()
		{
			stringstream ret;
			ret << "Button Input: " << id << endl;
			ret << " - Keyboard: " << keyboardMapping << endl;
			ret << " - Joystick: " << joystickMapping << endl;
			ret << " - Mouse: " << mouseMapping;
			return ret.str();
		}

		string GetStatus()
		{
			stringstream ret;
			ret << "Button Input " << id << ": " << pressed << "::" << down << "::" << released;
			return ret.str();
		}

		InputID id;
		int keyboardMapping;
		int joystickMapping;
		int mouseMapping;

		bool pressed;
		bool down;
		bool released;
	};

	struct AxisInput
	{
		AxisInput()
		{
			id = AxisID::AxisIDMax;
			keyboardHighMapping = -1;
			keyboardLowMapping = -1;
			joystickHighMapping = -1;
			joystickLowMapping = -1;
			mouseHighMapping = -1;
			mouseLowMapping = -1;

			highPressed = false;
			lowPressed = false;
			highDown = false;
			lowDown = false;
			highReleased = false;
			lowReleased = false;
			value = 0;
		}

		string ToString()
		{
			stringstream ret;
			ret << "Axis Input: " << id << endl;
			ret << " - Keyboard High: " << keyboardHighMapping << endl;
			ret << " - Keyboard Low: " << keyboardLowMapping << endl;
			ret << " - Joystick High: " << joystickHighMapping << endl;
			ret << " - Joystick Low: " << joystickLowMapping << endl;
			ret << " - Mouse High: " << mouseHighMapping << endl;
			ret << " - Mouse Low: " << mouseLowMapping;
			return ret.str();
		}

		string GetStatus()
		{
			stringstream ret;
			ret << "Axis Input " << id << ": " << value << endl << "\tHIGH: " << highPressed << "::" << highDown << "::" << highReleased << "\tLOW:  " << lowPressed << "::" << lowDown << "::" << lowReleased;
			return ret.str();
		}

		AxisID id;
		int keyboardLowMapping;
		int keyboardHighMapping;
		int joystickLowMapping;
		int joystickHighMapping;
		int mouseLowMapping;
		int mouseHighMapping;

		bool highPressed;
		bool lowPressed;
		bool highDown;
		bool lowDown;
		bool highReleased;
		bool lowReleased;
		float value;
	};

	static InputManager* instance;

	void LoadInputConfig();
	void SaveInputConfig();
	void UpdateInput();

	vector<ButtonInput> buttonInputs;
	vector<AxisInput> axisInputs;
	Text debugText;
};

#endif
