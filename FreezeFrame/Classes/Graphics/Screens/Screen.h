#ifndef FF_SCREEN
#define FF_SCREEN

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../ScreenManager.h"

using namespace std;
using namespace sf;

class Screen
{
public:

	virtual void Load() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(RenderWindow *window) = 0;
	virtual void Unload() = 0;

private:
	
};

#endif
