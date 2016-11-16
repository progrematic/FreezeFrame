#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Classes/Graphics/ScreenManager.h"

using namespace std;
using namespace sf;

#define PI 3.14159

int main()
{
	RenderWindow window(VideoMode(1280, 720), "Freeze Frame");
	ScreenManager::GetInstance()->LoadScreens();	//This forces the screen manager to instantiate an instance of itself so that everything can load up
	
	Clock dtClock;
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed || (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape))
				window.close();
			ScreenManager::GetInstance()->PollEvent(e);
		}
		Time dt = dtClock.restart();

		ScreenManager::GetInstance()->Update(dt.asSeconds());

		window.clear();
		ScreenManager::GetInstance()->Draw(&window);
		window.display();
	}

	return 0;
}