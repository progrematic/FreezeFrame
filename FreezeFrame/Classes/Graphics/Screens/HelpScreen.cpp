#include "HelpScreen.h"
#include "../../../Globals.h"

HelpScreen::HelpScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "BG.png"))
	{
		cout << "ERROR (HelpScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "BG.png" << endl;
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
	if (e.type == Event::KeyPressed && e.key.code == Keyboard::BackSpace)
	{
		ScreenManager::GetInstance()->PopScreen();
	}
}

void HelpScreen::Update(float dt)
{

}

void HelpScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
}

void HelpScreen::Unload()
{

}
