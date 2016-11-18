#include "CustomizeInputScreen.h"
#include "../../Globals.h"

CustomizeInputScreen::CustomizeInputScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "BG.png"))
	{
		cout << "ERROR (CustomizeInputScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "BG.png" << endl;
	}

	bgSprite = Sprite(bgTexture);
	titleText = Text("Customize Input", ScreenManager::GetInstance()->GetFont(), 50);
}

CustomizeInputScreen::~CustomizeInputScreen()
{

}

void CustomizeInputScreen::Load()
{

}

void CustomizeInputScreen::PollEvent(Event e)
{
	if (e.type == Event::KeyPressed && e.key.code == Keyboard::BackSpace)
	{
		ScreenManager::GetInstance()->PopScreen();
	}
}

void CustomizeInputScreen::Update(float dt)
{

}

void CustomizeInputScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
}

void CustomizeInputScreen::Unload()
{

}
