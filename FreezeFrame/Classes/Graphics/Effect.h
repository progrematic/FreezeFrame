#ifndef FF_EFFECT
#define FF_EFFECT

#include <SFML/Graphics.hpp>

class Effect
{
public:
	Effect();
	Effect(float _amplitude, float _period, float _xOffset, float _yOffset);

	float Calculate();
	float Calculate(float x);

	void SetFunction(float(*_func)(float));
	void SetValues(float _amplitude, float _period, float _xOffset, float _yOffset);
	void SetAbsolute(bool _absolute);

	void Reset();
	int GetCycles();

	sf::Clock& GetClock();
private:
	float(*func)(float);

	bool absolute;
	float amplitude;
	float period;
	float xOffset;
	float yOffset;

	int lastDiff;
	float lastVal;
	int topHits;
	int botHits;
	int cycles;

	sf::Clock clock;
};

#endif
