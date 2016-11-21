#ifndef FF_CUSTOMIZEINPUTSCREEN
#define FF_CUSTOMIZEINPUTSCREEN

#include "../Managers/ScreenManager.h"
#include "../Managers/InputManager.h"
#include "../UI/Menu.h"

class CustomizeInputScreen : public Screen
{
public:
	CustomizeInputScreen();
	~CustomizeInputScreen();

	void Load() override;
	void PollEvent(Event e) override;
	void Update(float dt) override;
	void Draw(RenderWindow* window) override;
	void Unload() override;

	ScreenID GetScreenID() { return ScreenID::CustomizeInputScreen; }
private:
	Texture bgTexture;
	Sprite bgSprite;
	Menu menu;

	Text titleText;
};
#endif
