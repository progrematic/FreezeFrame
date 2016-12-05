#include "TitleScreen.h"
#include "../../Globals.h"

TitleScreen::TitleScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "TitanSouls.jpg"))
	{
		cout << "ERROR (TitleScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "TitanSouls.jpg" << endl;
	}

	bgSprite = Sprite(bgTexture);
	titleText = Text("Freeze Frame", ScreenManager::GetInstance()->GetFont(), 100);
	titleText.setFillColor(Color(0, 0, 0, 255));
	pressStartText = Text("Press Start", ScreenManager::GetInstance()->GetFont(), 75);
	pressStartText.setFillColor(Color(0, 0, 0, 255));

	Vector2u windowSize = ScreenManager::GetInstance()->GetWindowSize();
	mainMenu.SetPosition(Vector2f(((float)windowSize.x / 2), (float)windowSize.y / 2));
	titleText.setPosition((windowSize.x - titleText.getLocalBounds().width) / 2, 0);
	pressStartText.setPosition((windowSize.x - pressStartText.getLocalBounds().width) / 2, windowSize.y - pressStartText.getLocalBounds().height - 50);
	pressStartFadeEffect = Effect(0.5f, 5, 0, 0.5f);
	pressStartFadeEffect.SetFunction(sin);

	state = State::PressStart;
}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::Load()
{
	MenuItem* test = new MenuItem();
	test->GetText().setString("Singleplayer");
	mainMenu.AddMenuItem(test);

	MenuItem* test2 = new MenuItem();
	test2->GetText().setString("Multiplayer");
	mainMenu.AddMenuItem(test2);

	MenuItem* test3 = new MenuItem();
	test3->GetText().setString("Settings");
	test3->SetOnSelect([](void* caller) { ScreenManager::GetInstance()->PushScreen(Screen::ScreenID::SettingsScreen); });
	mainMenu.AddMenuItem(test3);

	MenuItem* test4 = new MenuItem();
	test4->GetText().setString("Help");
	test4->SetOnSelect([](void* caller) { ScreenManager::GetInstance()->PushScreen(Screen::ScreenID::HelpScreen); });
	mainMenu.AddMenuItem(test4);

	MenuItem* test5 = new MenuItem();
	test5->GetText().setString("Exit");
	test5->SetOnSelect([](void* caller) { ScreenManager::GetInstance()->GetWindow()->close(); });
	mainMenu.AddMenuItem(test5);

	mainMenu.SetSelectedItemIndex(0);
}

void TitleScreen::PollEvent(Event e)
{
	mainMenu.PollEvent(e);
}

void TitleScreen::Update(float dt)
{
	mainMenu.Update(dt);

	switch (state)
	{
		case State::PressStart:
		{
			if (InputManager::GetInstance()->IsButtonPressed(0, InputManager::InputID::A))
			{
				state = State::MainMenu;
			}
			break;
		}
	}

	switch (state)
	{
		case State::PressStart:
		{
			Color pressStartTextColor = pressStartText.getFillColor();
			pressStartTextColor.a = (int)(pressStartFadeEffect.Calculate() * 255);
			pressStartText.setFillColor(pressStartTextColor);
			break;
		}
	}
}

void TitleScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
	switch (state)
	{
	case State::PressStart:
		window->draw(pressStartText);
		break;
	case State::MainMenu:
		mainMenu.Draw(window);
		break;
	}
}

void TitleScreen::Unload()
{
	mainMenu.ClearMenuItems();
}
