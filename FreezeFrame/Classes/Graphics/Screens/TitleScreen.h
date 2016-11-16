#ifndef FF_TITLESCREEN
#define FF_TITLESCREEN

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../ScreenManager.h"
#include "../Effect.h"

using namespace std;
using namespace sf;

class TitleScreen : public Screen
{
public:
	TitleScreen();
	~TitleScreen();

	void Load() override;
	void PollEvent(Event e) override;
	void Update(float dt) override;
	void Draw(RenderWindow* window) override;
	void Unload() override;

	ScreenID GetScreenID() { return ScreenID::TitleScreen; }
private:
	Texture bgTexture;
	Sprite bgSprite;

	Text titleText;
};

#endif
