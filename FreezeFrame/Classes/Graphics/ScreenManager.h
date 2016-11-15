#ifndef FF_SCREENMANAGER
#define FF_SCREENMANAGER

#include <SFML/Graphics.hpp>
#include "Screens/Screen.h"
#include "../../Globals.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Screen;
class ScreenManager
{
public:
	static ScreenManager* GetInstance();

	ScreenManager();
	~ScreenManager();

	void LoadScreens();

	void Update(float dt);
	void Draw(RenderWindow* window);

	Font& GetFont();

private:
	static ScreenManager* instance;

	vector<Screen*> screens;
	int curScreen;

	Font gameFont;
};

#endif
