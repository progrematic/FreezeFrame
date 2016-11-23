#include "Menu.h"

Menu::Menu()
{
	shouldUpdateArrangement = true;
	itemSeparation = 10;
}

Menu::~Menu()
{
	ClearMenuItems();
}

void Menu::AddMenuItem(MenuItem* menuItem)
{
	menuItems.push_back(menuItem);
	shouldUpdateArrangement = true;
}

void Menu::PollEvent(Event e)
{

}

void Menu::Update(float dt)
{
	if (shouldUpdateArrangement)
		UpdateArrangement();

	for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
	{
		(*it)->Update(dt);
	}
}

void Menu::Draw(RenderWindow* window)
{
	for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
	{
		(*it)->Draw(window);
	}
}

void Menu::SetVisible(bool visible)
{
	for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
	{
		(*it)->SetVisible(visible);
	}
}

void Menu::SetPosition(Vector2f pos)
{
	position = pos;
	UpdateArrangement();
}

void Menu::SetItemSeparation(float _itemSeparation)
{
	itemSeparation = _itemSeparation;
	UpdateArrangement();
}

void Menu::ClearMenuItems()
{
	for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
	{
		delete(*it);
	}
	menuItems.clear();
}

void Menu::UpdateArrangement()
{
	int i = 0;
	for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
	{
		(*it)->SetPosition(Vector2f(position.x - ((*it)->GetBackground().getTextureRect().width / 2), position.y + (i * (*it)->GetBackground().getTextureRect().height) + (i * itemSeparation)));
		i++;
	}

	shouldUpdateArrangement = false;
}
