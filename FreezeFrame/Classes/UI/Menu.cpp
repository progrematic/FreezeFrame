#include "Menu.h"

Menu::Menu()
{
	shouldUpdateArrangement = true;
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

void Menu::SetPosition(Vector2f pos)
{
	position = pos;
	UpdateArrangement();
}

void Menu::ClearMenuItems()
{
	for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
	{
		free(*it);
	}
	menuItems.clear();
}

void Menu::UpdateArrangement()
{
	int i = 0;
	for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
	{
		(*it)->SetPosition(Vector2f(position.x, position.y + (i * (*it)->GetBackground().getTextureRect().height)));
		i++;
	}

	shouldUpdateArrangement = false;
}
