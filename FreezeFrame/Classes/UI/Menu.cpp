#include "Menu.h"
#include "../Managers/InputManager.h"

Menu::Menu()
{
	shouldUpdateArrangement = true;
	itemSeparation = 10;
	selectedItemIndex = 0;
	selected = true;
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

	if (selected)
	{
		for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
		{
			(*it)->Update(dt);
		}

		if (InputManager::GetInstance()->IsHighAxisButtonPressed(0, InputManager::AxisID::LVertical))
		{
			SetSelectedItemIndex(selectedItemIndex == (menuItems.size() - 1) ? 0 : selectedItemIndex + 1);
		}
		if (InputManager::GetInstance()->IsLowAxisButtonPressed(0, InputManager::AxisID::LVertical))
		{
			SetSelectedItemIndex(selectedItemIndex == 0 ? (menuItems.size() - 1) : selectedItemIndex - 1);
		}
		if (InputManager::GetInstance()->IsButtonPressed(0, InputManager::InputID::A))
		{
			GetSelectedMenuItem()->Select();
		}
	}
}

void Menu::Draw(RenderWindow* window)
{
	if (selected)
	{
		for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
		{
			(*it)->Draw(window);
		}
	}
}

void Menu::SetSelected(bool _selected)
{
	selected = _selected;
}

void Menu::SetSelectedItemIndex(int _selectedItemIndex)
{
	menuItems[selectedItemIndex]->Unhighlight();
	selectedItemIndex = _selectedItemIndex;
	menuItems[selectedItemIndex]->Highlight();
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

MenuItem* Menu::GetSelectedMenuItem()
{
	return menuItems[selectedItemIndex];
}
