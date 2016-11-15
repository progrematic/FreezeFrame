#include "ScreenManager.h"

#include "Screens/TitleScreen.h"

ScreenManager* ScreenManager::instance = NULL;

ScreenManager::ScreenManager()
{
	if (instance)
	{
		cout << "ERROR (ScreenManager) : Attempting to instantiate ScreenManager directly. This is not allowed!" << endl;
		return;
	}

	if (!gameFont.loadFromFile(ASSETS_FONTS_PATH "arial.ttf"))
	{
		cout << "ERROR (ScreenManager) : Unable to load font " << ASSETS_FONTS_PATH << "arial.ttf" << endl;
	}
}

ScreenManager::~ScreenManager()
{
	for (int i = 0; i < screens.size(); i++)
	{
		delete screens[i];
	}
}

ScreenManager* ScreenManager::GetInstance()
{
	if (!instance)
	{
		instance = new ScreenManager();
	}
	return instance;
}

void ScreenManager::LoadScreens()
{
	screens.push_back(new TitleScreen());
	curScreen = 0;

	screens[curScreen]->Load();
}

void ScreenManager::Update(float dt)
{
	screens[curScreen]->Update(dt);
}

void ScreenManager::Draw(RenderWindow* window)
{
	screens[curScreen]->Draw(window);
}

Font& ScreenManager::GetFont()
{
	return gameFont;
}