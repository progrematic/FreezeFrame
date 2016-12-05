#include "CustomizeInputScreen.h"
#include "../../Globals.h"

CustomizeInputScreen::CustomizeInputScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "TitanSouls.jpg"))
	{
		cout << "ERROR (CustomizeInputScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "TitanSouls.jpg" << endl;
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

}

void CustomizeInputScreen::Update(float dt)
{
	if (InputManager::GetInstance()->IsButtonPressed(0, InputManager::InputID::B))
	{
		ScreenManager::GetInstance()->PopScreen();
		return;
	}
}

void CustomizeInputScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
}

void CustomizeInputScreen::Unload()
{

}
