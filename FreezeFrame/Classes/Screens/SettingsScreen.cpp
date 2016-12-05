#include "SettingsScreen.h"
#include "../../Globals.h"

SettingsScreen::SettingsScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "TitanSouls.jpg"))
	{
		cout << "ERROR (SettingsScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "TitanSouls.jpg" << endl;
	}

	bgSprite = Sprite(bgTexture);
	titleText = Text("Settings", ScreenManager::GetInstance()->GetFont(), 50);
	titleText.setFillColor(Color(0, 0, 0, 255));

	Vector2u windowSize = ScreenManager::GetInstance()->GetWindowSize();
	titleText.setPosition((windowSize.x - titleText.getLocalBounds().width) / 2, 0);
	menu.SetPosition(Vector2f(((float)windowSize.x / 2), (float)windowSize.y / 2));
	audioMenu.SetPosition(Vector2f(((float)windowSize.x / 2), (float)windowSize.y / 2));
	videoMenu.SetPosition(Vector2f(((float)windowSize.x / 2), (float)windowSize.y / 2));

	audioMenu.SetVisible(false);
	audioMenu.SetSelected(false);
	videoMenu.SetVisible(false);
	videoMenu.SetSelected(false);
}

SettingsScreen::~SettingsScreen()
{

}

void SettingsScreen::Load()
{
	MenuItem* test = new MenuItem();
	test->GetText().setString("Audio");
	test->SetOnSelect([](void* caller) { ((SettingsScreen*)caller)->ShowAudioMenu(); }, this);
	menu.AddMenuItem(test);

	MenuItem* test2 = new MenuItem();
	test2->GetText().setString("Video");
	test2->SetOnSelect([](void* caller) { ((SettingsScreen*)caller)->ShowVideoMenu(); }, this);
	menu.AddMenuItem(test2);

	MenuItem* test3 = new MenuItem();
	test3->GetText().setString("Input");
	test3->SetOnSelect([](void*) { ScreenManager::GetInstance()->PushScreen(Screen::ScreenID::CustomizeInputScreen); });
	menu.AddMenuItem(test3);

	MenuItem* test4 = new MenuItem();
	test4->GetText().setString("Back");
	test4->SetOnSelect([](void*) { ScreenManager::GetInstance()->PopScreen(); });
	menu.AddMenuItem(test4);

	menu.SetSelectedItemIndex(0);

	MenuItem* atest = new MenuItem();
	atest->GetText().setString("Master Volume");
	audioMenu.AddMenuItem(atest);

	MenuItem* atest2 = new MenuItem();
	atest2->GetText().setString("BGM Volume");
	audioMenu.AddMenuItem(atest2);

	MenuItem* atest3 = new MenuItem();
	atest3->GetText().setString("SFX Volume");
	audioMenu.AddMenuItem(atest3);

	MenuItem* atest4 = new MenuItem();
	atest4->GetText().setString("Back");
	atest4->SetOnSelect([](void* caller) { ((SettingsScreen*)caller)->BackToMenu(); }, this);
	audioMenu.AddMenuItem(atest4);

	audioMenu.SetSelectedItemIndex(0);

	MenuItem* vtest = new MenuItem();
	vtest->GetText().setString("Resolution");
	videoMenu.AddMenuItem(vtest);

	MenuItem* vtest2 = new MenuItem();
	vtest2->GetText().setString("Fullscreen");
	videoMenu.AddMenuItem(vtest2);

	MenuItem* vtest3 = new MenuItem();
	vtest3->GetText().setString("Back");
	vtest3->SetOnSelect([](void* caller) { ((SettingsScreen*)caller)->BackToMenu(); }, this);
	videoMenu.AddMenuItem(vtest3);

	videoMenu.SetSelectedItemIndex(0);
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
	menu.Update(dt);
	audioMenu.Update(dt);
	videoMenu.Update(dt);
}

void SettingsScreen::Draw(RenderWindow* window)
{
	window->draw(bgSprite);
	window->draw(titleText);
	menu.Draw(window);
	audioMenu.Draw(window);
	videoMenu.Draw(window);
}

void SettingsScreen::Unload()
{
	menu.ClearMenuItems();
	audioMenu.ClearMenuItems();
	videoMenu.ClearMenuItems();
}

void SettingsScreen::ShowAudioMenu()
{
	videoMenu.SetVisible(false);
	videoMenu.SetSelected(false);
	menu.SetVisible(false);
	menu.SetSelected(false);
	audioMenu.SetVisible(true);
	audioMenu.SetSelected(true);
}

void SettingsScreen::ShowVideoMenu()
{
	menu.SetVisible(false);
	menu.SetSelected(false);
	audioMenu.SetVisible(false);
	audioMenu.SetSelected(false);
	videoMenu.SetVisible(true);
	videoMenu.SetSelected(true);
}

void SettingsScreen::BackToMenu()
{
	audioMenu.SetVisible(false);
	audioMenu.SetSelected(false);
	videoMenu.SetVisible(false);
	videoMenu.SetSelected(false);
	menu.SetVisible(true);
	menu.SetSelected(true);
}
