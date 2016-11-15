#ifndef FF_TITLESCREEN
#define FF_TITLESCREEN

#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace sf;

class TitleScreen : public Screen
{
public:
	TitleScreen();
	~TitleScreen();

	void Load() override;
	void Update(float dt) override;
	void Draw(RenderWindow* window) override;
	void Unload() override;

private:
	Texture bgTexture;
	vector<Sprite*> bgSprites;
	int bgSpriteNum;
	float bgSpeed;

	Text titleText;
};

#endif
