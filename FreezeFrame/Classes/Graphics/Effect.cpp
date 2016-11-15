#include "Effect.h"

#define CLOSE_ENOUGH 0.0000000005f

Effect::Effect()
{
	SetFunction(sin);
	SetValues(1, 1, 0, 0);
	absolute = false;
	Reset();
}

Effect::Effect(float _amplitude, float _period, float _xOffset, float _yOffset) : Effect()
{
	SetValues(_amplitude, _period, _xOffset, _yOffset);
}

float Effect::Calculate()
{
	return Calculate(clock.getElapsedTime().asSeconds());
}

float Effect::Calculate(float x)
{
	float val = amplitude * (func(period * (x - xOffset))) + yOffset;

	int diff = 0;
	if (lastVal > val)
		diff = -1;
	else
		diff = 1;

	if (diff == 1 && lastDiff == -1)
	{
		botHits++;
		if (topHits == botHits)
			cycles++;
	}
	else if (diff == -1 && lastDiff == 1)
	{
		topHits++;
		if (topHits == botHits)
			cycles++;
	}
	//printf("%d --- %d::%d\n", cycles, topHits, botHits);
	
	lastVal = val;
	lastDiff = diff;
	return absolute ? abs(val) : val;
}

void Effect::SetFunction(float(*_func)(float))
{
	func = _func;
}

void Effect::SetValues(float _amplitude, float _period, float _xOffset, float _yOffset)
{
	amplitude = _amplitude;
	period = _period;
	xOffset = _xOffset;
	yOffset = _yOffset;
}

void Effect::SetAbsolute(bool _absolute)
{
	absolute = _absolute;
}

void Effect::Reset()
{
	lastVal = 0;
	lastDiff = 1;
	cycles = 0;
	topHits = 0;
	botHits = 0;
	clock.restart();
}

int Effect::GetCycles()
{
	return cycles;
}

sf::Clock& Effect::GetClock()
{
	return clock;
}