#ifndef FF_ACTOR
#define FF_ACTOR

#include <SFML/Graphics.hpp>

using namespace sf;

class Actor
{
public:
	Actor();
	void Initialize(Texture _texture);

	Sprite& GetSprite();

private:
	Sprite sprite;
};

#endif
