#ifndef FF_MENUITEM
#define FF_MENUITEM

#include <SFML/Graphics.hpp>
#include <functional>
using namespace sf;
using namespace std;

class MenuItem
{
public:
	MenuItem();

	void SetBackground(Texture _texture);
	
	Sprite& GetBackground();
	Text& GetText();

	void Update(float dt);
	void Draw(RenderWindow* window);

	void Highlight();
	void Unhighlight();
	void Select();

	void SetVisible(bool visible);
	void SetPosition(Vector2f pos);
	void SetOnSelect(void(*_onSelect)(void* caller), void* arg = NULL);

private:
	Texture texture;
	Sprite background;
	Text text;
	bool highlighted;
	void (*onSelect)(void* caller);
	void* onSelectArg;
};

#endif
