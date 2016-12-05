#include "MenuItem.h"
#include "../Managers/ScreenManager.h"

#define SELECTED_X_SCALE 1.1f
#define SELECTED_Y_SCALE 1.1f

MenuItem::MenuItem()
{
	if (!texture.loadFromFile(ASSETS_ART_UI_PATH "ButtonBackground.png"))
	{
		cout << "ERROR (MenuItem) : Failure to load Texture: " << ASSETS_ART_UI_PATH << "ButtonBackground.png" << endl;
		return;
	}
	background = Sprite(texture);
	text = Text("Menu Item", ScreenManager::GetInstance()->GetFont(), 40);
	highlighted = false;
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

void MenuItem::Highlight()
{
	if (!highlighted)
	{
		highlighted = true;
		background.setScale(SELECTED_X_SCALE, SELECTED_Y_SCALE);
		float widthDiff  = background.getTextureRect().width  * (SELECTED_X_SCALE - 1);
		float heightDiff = background.getTextureRect().height * (SELECTED_Y_SCALE - 1);
		background.move(-widthDiff/2, -heightDiff/2);
	}
}

void MenuItem::Unhighlight()
{
	if (highlighted)
	{
		highlighted = false;
		background.setScale(1, 1);
		float widthDiff = background.getTextureRect().width  * (SELECTED_X_SCALE - 1);
		float heightDiff = background.getTextureRect().height * (SELECTED_Y_SCALE - 1);
		background.move(widthDiff / 2, heightDiff / 2);
	}
}

void MenuItem::Select()
{
	if (onSelect)
		onSelect(onSelectArg);
}

void MenuItem::SetOnSelect(void(*_onSelect)(void* caller), void* arg)
{
	onSelect = _onSelect;
	onSelectArg = arg;
}

Sprite& MenuItem::GetBackground()
{
	return background;
}

Text& MenuItem::GetText()
{
	return text;
}

void MenuItem::SetVisible(bool visible)
{
	background.setColor(Color(255, 255, 255, visible ? 255 : 0));
	text.setFillColor(Color(255, 255, 255, visible ? 255 : 0));
}

void MenuItem::SetPosition(Vector2f pos)
{
	background.setPosition(pos);
	float textOffset = (background.getTextureRect().width - text.getLocalBounds().width) / 2;
	text.setPosition(pos + Vector2f(textOffset, 0));
	if (highlighted)
	{
		float widthDiff = background.getTextureRect().width  * (SELECTED_X_SCALE - 1);
		float heightDiff = background.getTextureRect().height * (SELECTED_Y_SCALE - 1);
		background.move(-widthDiff / 2, -heightDiff / 2);
	}
}
