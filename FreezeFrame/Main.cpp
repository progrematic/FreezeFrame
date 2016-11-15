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
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				window.close();
		}
		Time dt = dtClock.restart();

		ScreenManager::GetInstance()->Update(dt.asSeconds());

		window.clear();
		ScreenManager::GetInstance()->Draw(&window);
		window.display();
	}

	return 0;
}