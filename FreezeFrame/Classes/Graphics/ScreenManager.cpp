#include "ScreenManager.h"

#include "Screens/TitleScreen.h"
#include "Screens/SettingsScreen.h"
#include "Screens/HelpScreen.h"

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
	screens.push_back(new SettingsScreen());
	screens.push_back(new HelpScreen());
	screenStack.push_back(Screen::ScreenID::TitleScreen);

	GetCurrentScreen()->Load();
}

void ScreenManager::PollEvent(Event e)
{
	GetCurrentScreen()->PollEvent(e);
}

void ScreenManager::Update(float dt)
{
	GetCurrentScreen()->Update(dt);
}

void ScreenManager::Draw(RenderWindow* window)
{
	GetCurrentScreen()->Draw(window);
}

void ScreenManager::PushScreen(Screen::ScreenID screen)
{
	bool validScreen = false;
	for (int i = 0; i < screens.size(); i++)
	{
		if (screens[i]->GetScreenID() == screen)
		{
			validScreen = true;
			break;
		}
	}

	if (validScreen)
	{
		GetCurrentScreen()->Unload();
		screenStack.push_back(screen);
		GetCurrentScreen()->Load();
	}
	else
	{
		cout << "Error: (ScreenManager) - Attempting to push an invalid screen: " << screen << endl;
	}
}

void ScreenManager::PopScreen()
{
	if (screenStack.size() > 1)
	{
		GetCurrentScreen()->Unload();
		screenStack.pop_back();
		GetCurrentScreen()->Load();
	}
	else
	{
		cout << "Error: (ScreenManager) - Attempting to pop screen when there are no more left in the stack" << endl;
	}
}

Font& ScreenManager::GetFont()
{
	return gameFont;
}

int ScreenManager::GetCurrentScreenID()
{
	if (screenStack.size() > 0)
		return ((int)screenStack[screenStack.size() - 1]);
	return -1;
}

Screen* ScreenManager::GetCurrentScreen()
{
	if (screens.size() > 0)
		return screens[GetCurrentScreenID()];
	return NULL;
}