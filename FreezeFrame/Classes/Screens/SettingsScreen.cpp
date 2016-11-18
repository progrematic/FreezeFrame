#include "SettingsScreen.h"
#include "../../Globals.h"

SettingsScreen::SettingsScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "BG.png"))
	{
		cout << "ERROR (SettingsScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "BG.png" << endl;
	}

	bgSprite = Sprite(bgTexture);
	titleText = Text("Settings", ScreenManager::GetInstance()->GetFont(), 50);
}

SettingsScreen::~SettingsScreen()
{

}

void SettingsScreen::Load()
{

}

void SettingsScreen::PollEvent(Event e)
{
	if (e.type == Event::KeyPressed && e.key.code == Keyboard::BackSpace)
	{
		ScreenManager::GetInstance()->PopScreen();
	}
	else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Return)
	{
		ScreenManager::GetInstance()->PushScreen(ScreenID::CustomizeInputScreen);
	}
}

void SettingsScreen::Update(float dt)
{

}

void SettingsScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
}

void SettingsScreen::Unload()
{

}
