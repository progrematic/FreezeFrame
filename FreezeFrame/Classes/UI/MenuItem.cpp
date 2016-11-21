#include "MenuItem.h"
#include "../Managers/ScreenManager.h"

MenuItem::MenuItem()
{
	if (!texture.loadFromFile(ASSETS_ART_UI_PATH "ButtonBackground.png"))
	{
		cout << "ERROR (MenuItem) : Failure to load Texture: " << ASSETS_ART_UI_PATH << "ButtonBackground.png" << endl;
		return;
	}
	background = Sprite(texture);
	text = Text("Menu Item", ScreenManager::GetInstance()->GetFont(), 40);
}

void MenuItem::SetBackground(Texture _texture)
{
	texture = _texture;
	background = Sprite(texture);
}

void MenuItem::Update(float dt)
{

}

void MenuItem::Draw(RenderWindow* window)
{
	window->draw(background);
	window->draw(text);
}

Sprite& MenuItem::GetBackground()
{
	return background;
}

Text& MenuItem::GetText()
{
	return text;
}

void MenuItem::SetPosition(Vector2f pos)
{
	background.setPosition(pos);
	float textOffset = (background.getTextureRect().width - text.getLocalBounds().width) / 2;
	text.setPosition(pos + Vector2f(textOffset, 0));
}
