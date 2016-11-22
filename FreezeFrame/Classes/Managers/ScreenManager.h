#ifndef FF_SCREENMANAGER
#define FF_SCREENMANAGER

#include <SFML/Graphics.hpp>
#include "../../Globals.h"
#include "../Managers/InputManager.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Screen
{
public:
	enum ScreenID
	{
		TitleScreen,
		SettingsScreen,
		HelpScreen,
		CustomizeInputScreen,
		ScreenIDMax
	};

	virtual void Load() = 0;
	virtual void PollEvent(Event e) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(RenderWindow *window) = 0;
	virtual void Unload() = 0;

	virtual ScreenID GetScreenID() = 0;

private:

};

class ScreenManager
{
public:
	static ScreenManager* GetInstance();

	ScreenManager();
	~ScreenManager();

	void LoadScreens();

	void PollEvent(Event e);
	void Update(float dt);
	void Draw(RenderWindow* window);
	
	void PushScreen(Screen::ScreenID screen);
	void PopScreen();

	void SetWindow(RenderWindow* _window);
	RenderWindow* GetWindow();
	Font& GetFont();

private:
	static ScreenManager* instance;

	int GetCurrentScreenID();
	Screen* GetCurrentScreen();

	vector<Screen*> screens;
	vector<Screen::ScreenID> screenStack;

	RenderWindow* window;
	Font gameFont;
};

#endif
