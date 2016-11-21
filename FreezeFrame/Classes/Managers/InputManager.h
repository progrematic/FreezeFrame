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

	bool IsButtonPressed(int playerId, InputID inputId);
	bool IsButtonDown(int playerId, InputID inputId);
	bool IsButtonReleased(int playerId, InputID inputId);
	bool IsHighAxisButtonPressed(int playerId, AxisID inputId);
	bool IsHighAxisButtonDown(int playerId, AxisID inputId);
	bool IsHighAxisButtonReleased(int playerId, AxisID inputId);
	bool IsLowAxisButtonPressed(int playerId, AxisID inputId);
	bool IsLowAxisButtonDown(int playerId, AxisID inputId);
	bool IsLowAxisButtonReleased(int playerId, AxisID inputId);
	float GetAxisValue(int playerId, AxisID axisId);

private:
	struct ButtonInput
	{
		ButtonInput();
		string ToString();
		string GetStatus();

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
		AxisInput();
		string ToString();
		string GetStatus();

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

	struct PlayerInput
	{
		vector<ButtonInput> buttonInputs;
		vector<AxisInput> axisInputs;
	};

	static InputManager* instance;

	void LoadInputConfig();
	void SaveInputConfig();
	void UpdateInput();

	vector <PlayerInput> playerInputs;

	Text debugText;
};

#endif
