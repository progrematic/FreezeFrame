#include "TitleScreen.h"
#include "../../Globals.h"

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

}

void TitleScreen::Update(float dt)
{
	if (InputManager::GetInstance()->IsButtonPressed(0, InputManager::InputID::A))
	{
		ScreenManager::GetInstance()->PushScreen(Screen::ScreenID::SettingsScreen);
	}
}

void TitleScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
}

void TitleScreen::Unload()
{

}
