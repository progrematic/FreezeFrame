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
	MenuItem* test = new MenuItem();
	test->GetText().setString("Test Menu Item");
	menu.AddMenuItem(test);

	MenuItem* test2 = new MenuItem();
	test2->GetText().setString("Test Menu Item 2");
	menu.AddMenuItem(test2);

	menu.SetPosition(Vector2f(150, 150));
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

	menu.Update(dt);
}

void CustomizeInputScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
	menu.Draw(window);
}

void CustomizeInputScreen::Unload()
{
	menu.ClearMenuItems();
}
