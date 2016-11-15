#include "TitleScreen.h"
#include "../../../Globals.h"

TitleScreen::TitleScreen()
{
	if (!bgTexture.loadFromFile(ASSETS_ART_BACKGROUNDS_PATH "BG.png"))
	{
		cout << "ERROR (TitleScreen) : Failure to load Texture: " << ASSETS_ART_BACKGROUNDS_PATH << "BG.png";
	}

	bgSpriteNum = 3;
	for (int i = 0; i < bgSpriteNum; i++)
	{
		bgSprites.push_back(new Sprite(bgTexture));
		if (i > 0)
		{
			bgSprites[i]->move(bgTexture.getSize().x * i, 0);
		}
	}
	bgSpeed = 500;

	titleText = Text("Freeze Frame", ScreenManager::GetInstance()->GetFont(), 50);
}

TitleScreen::~TitleScreen()
{
	for (int i = 0; i < bgSpriteNum; i++)
	{
		delete bgSprites[i];
	}
}

void TitleScreen::Load()
{

}

void TitleScreen::Update(float dt)
{
	for (int i = 0; i < bgSpriteNum; i++)
	{
		bgSprites[i]->move(-bgSpeed * dt, 0);
		if (bgSprites[i]->getPosition().x < bgSprites[i]->getTextureRect().width * -1)
		{
			bgSprites[i]->setPosition(bgSprites[i]->getTextureRect().width * (bgSpriteNum - 1), 0);
		}
	}
}

void TitleScreen::Draw(RenderWindow* window)
{
	for (int i = 0; i < bgSpriteNum; i++)
	{
		Sprite s = *bgSprites[i];
		window->draw(s);
	}
	window->draw(titleText);
}

void TitleScreen::Unload()
{

}
