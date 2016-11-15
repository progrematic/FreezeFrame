#include "Actor.h"

Actor::Actor()
{
	sprite = Sprite();
}

void Actor::Initialize(Texture _texture)
{
	sprite = Sprite(_texture);
}

Sprite& Actor::GetSprite()
{
	return sprite;
}