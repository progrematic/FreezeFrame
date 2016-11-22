#include "HelpScreen.h"
#include "../../Globals.h"

HelpScreen::HelpScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "TitanSouls.jpg"))
	{
		cout << "ERROR (HelpScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "TitanSouls.jpg" << endl;
	}

	bgSprite = Sprite(bgTexture);
	titleText = Text("Help", ScreenManager::GetInstance()->GetFont(), 50);
}

HelpScreen::~HelpScreen()
{

}

void HelpScreen::Load()
{

}

void HelpScreen::PollEvent(Event e)
{

}

void HelpScreen::Update(float dt)
{
	if (InputManager::GetInstance()->IsButtonPressed(0, InputManager::InputID::B))
	{
		ScreenManager::GetInstance()->PopScreen();
		return;
	}
}

void HelpScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
}

void HelpScreen::Unload()
{

}
