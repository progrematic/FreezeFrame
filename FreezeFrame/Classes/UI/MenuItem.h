#ifndef FF_MENUITEM
#define FF_MENUITEM

#include <SFML/Graphics.hpp>
using namespace sf;

class MenuItem
{
public:
	MenuItem();

	void SetBackground(Texture _texture);
	
	Sprite& GetBackground();
	Text& GetText();

	void Update(float dt);
	void Draw(RenderWindow* window);

	void SetPosition(Vector2f pos);

private:
	Texture texture;
	Sprite background;
	Text text;
};

#endif