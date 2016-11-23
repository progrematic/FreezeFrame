#ifndef FF_MENU
#define FF_MENU

#include <SFML/Graphics.hpp>
#include "MenuItem.h"

#include <vector>
using namespace std;

class Menu
{
public:
	Menu();
	~Menu();

	void AddMenuItem(MenuItem* menuItem);

	void PollEvent(Event e);
	void Update(float dt);
	void Draw(RenderWindow* window);

	void SetVisible(bool visible);
	void SetPosition(Vector2f pos);
	void SetItemSeparation(float _itemSeparation);
	void ClearMenuItems();

private:
	void UpdateArrangement();

	vector<MenuItem*> menuItems;
	bool shouldUpdateArrangement;

	Vector2f position;
	Vector2f size;
	float itemSeparation;
};

#endif
