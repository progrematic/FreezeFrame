#include "TitleScreen.h"
#include "../../../Globals.h"

TitleScreen::TitleScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "BG.png"))
	{
		cout << "ERROR (TitleScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "BG.png" << endl;
	}

	bgSprite = Sprite(bgTexture);
	titleText = Text("Freeze Frame", ScreenManager::GetInstance()->GetFont(), 50);
}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::Load()
{

}

void TitleScreen::PollEvent(Event e)
{
	if (e.type == Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case Keyboard::BackSpace:
			ScreenManager::GetInstance()->PopScreen();
			break;
		case Keyboard::Return:
			ScreenManager::GetInstance()->PushScreen(Screen::ScreenID::SettingsScreen);
			break;
		case Keyboard::Space:
			ScreenManager::GetInstance()->PushScreen(Screen::ScreenID::HelpScreen);
			break;
		case Keyboard::Tab:
			ScreenManager::GetInstance()->PushScreen(Screen::ScreenID::ScreenIDMax);
			break;
		}
	}
}

void TitleScreen::Update(float dt)
{

}

void TitleScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
}

void TitleScreen::Unload()
{

}
