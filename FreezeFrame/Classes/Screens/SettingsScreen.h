#ifndef FF_SETTINGSSCREEN
#define FF_SETTINGSSCREEN

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../Managers/ScreenManager.h"
#include "../UI/Menu.h"

using namespace std;
using namespace sf;

class SettingsScreen : public Screen
{
public:
	SettingsScreen();
	~SettingsScreen();

	void Load() override;
	void PollEvent(Event e) override;
	void Update(float dt) override;
	void Draw(RenderWindow* window) override;
	void Unload() override;

	ScreenID GetScreenID() { return ScreenID::SettingsScreen; }
private:
	Texture bgTexture;
	Sprite bgSprite;

	Text titleText;
	Menu menu;
	Menu audioMenu;
	Menu videoMenu;

	void ShowAudioMenu();
	void ShowVideoMenu();
	void BackToMenu();
};

#endif
