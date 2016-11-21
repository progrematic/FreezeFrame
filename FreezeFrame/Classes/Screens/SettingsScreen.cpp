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

}

void SettingsScreen::Update(float dt)
{
	if (InputManager::GetInstance()->IsButtonPressed(0, InputManager::InputID::B))
	{
		ScreenManager::GetInstance()->PopScreen();
		return;
	}
	if (InputManager::GetInstance()->IsButtonPressed(0, InputManager::InputID::A))
	{
		ScreenManager::GetInstance()->PushScreen(ScreenID::CustomizeInputScreen);
	}
}

void SettingsScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
}

void SettingsScreen::Unload()
{

}
