#ifndef FF_HELPSCREEN
#define FF_HELPSCREEN

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../ScreenManager.h"

using namespace std;
using namespace sf;

class HelpScreen : public Screen
{
public:
	HelpScreen();
	~HelpScreen();

	void Load() override;
	void PollEvent(Event e) override;
	void Update(float dt) override;
	void Draw(RenderWindow* window) override;
	void Unload() override;

	ScreenID GetScreenID() { return ScreenID::HelpScreen; }
private:
	Texture bgTexture;
	Sprite bgSprite;

	Text titleText;
};

#endif
