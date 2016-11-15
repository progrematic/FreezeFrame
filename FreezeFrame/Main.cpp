#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Classes/Graphics/Effect.h"

using namespace std;
using namespace sf;

#define PI 3.14159

int main()
{
	RenderWindow window(VideoMode(1280, 720), "SFML Window");
	Texture bgTexture;
	if (!bgTexture.loadFromFile("Assets/Art/Backgrounds/BG.png"))
	{
		system("pause");
		return EXIT_FAILURE;
	}
	Sprite bg(bgTexture);
	Sprite bg2(bgTexture);
	Sprite bg3(bgTexture);
	bg2.setPosition(bg.getPosition().x + bg.getTextureRect().width, 0);
	bg3.setPosition(bg2.getPosition().x + bg2.getTextureRect().width, 0);
	float xSpeed = 25;

	Font font;
	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		system("pause");
		return EXIT_FAILURE;
	}
	Text titleText("Freeze Frame", font, 50);

	Shader freezeFlashShader;
	if (!freezeFlashShader.loadFromFile("Assets/Shaders/FreezeFlash.frag", Shader::Type::Fragment))
	{
		system("pause");
		return EXIT_FAILURE;
	}
	freezeFlashShader.setUniform("texture", Shader::CurrentTexture);
	freezeFlashShader.setUniform("whiteout", Glsl::Vec4(1, 0, 0, 1));
	Effect freezeFlashEffect;
	freezeFlashEffect.SetFunction(cos);
	freezeFlashEffect.SetValues(1, 30, PI/30, 2);

	Shader pixelateShader;
	if (!pixelateShader.loadFromFile("Assets/Shaders/pixelate.frag", Shader::Type::Fragment))
	{
		system("pause");
		return EXIT_FAILURE;
	}
	pixelateShader.setUniform("texture", Shader::CurrentTexture);
	pixelateShader.setUniform("pixel_threshold", 0.0001f);
	Effect pixelateEffect;
	pixelateEffect.SetFunction(cos);
	pixelateEffect.SetValues(0.025f, 10, PI/10, 0.025f);

	Music bgm;
	if (!bgm.openFromFile("Assets/Audio/BGM/Soliloquy.ogg"))
	{
		system("pause");
		return EXIT_FAILURE;
	}
	//bgm.play();

	Effect* currentEffect = &freezeFlashEffect;
	Shader* currentShader = &freezeFlashShader;

	Clock dtClock;
	bool pixelate = false;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Space:
					pixelate = true;
					break;
				case Keyboard::Left:
					currentEffect = &freezeFlashEffect;
					currentShader = &freezeFlashShader;
					break;
				case Keyboard::Right:
					currentEffect = &pixelateEffect;
					currentShader = &pixelateShader;
				}
			}
		}
		
		Time dt = dtClock.restart();

		bg.move(-xSpeed * dt.asSeconds(), 0);
		bg2.move(-xSpeed * dt.asSeconds(), 0);
		bg3.move(-xSpeed * dt.asSeconds(), 0);

		if (bg.getPosition().x < bg.getTextureRect().width * -1)
		{
			bg.setPosition(bg3.getPosition().x + bg3.getTextureRect().width, 0);
		}
		if (bg2.getPosition().x < bg2.getTextureRect().width * -1)
		{
			bg2.setPosition(bg.getPosition().x + bg.getTextureRect().width, 0);
		}
		if (bg3.getPosition().x < bg3.getTextureRect().width * -1)
		{
			bg3.setPosition(bg2.getPosition().x + bg2.getTextureRect().width, 0);
		}
		
		if (pixelate)
		{
			float whiteout = currentEffect->Calculate();
			if (currentEffect == &freezeFlashEffect)
			{
				currentShader->setUniform("whiteout", Glsl::Vec4(whiteout, whiteout, whiteout, 1));
				pixelate = !(currentEffect->GetCycles() == 3);
			}
			else if (currentEffect == &pixelateEffect)
			{
				currentShader->setUniform("pixel_threshold", whiteout);
				pixelate = !(currentEffect->GetCycles() == 1);
			}
		}
		else
		{
			currentEffect->Reset();
			if (currentEffect == &freezeFlashEffect)
			{
				currentShader->setUniform("whiteout", Glsl::Vec4(1, 1, 1, 1));
			}
			else if (currentEffect == &pixelateEffect)
			{
				currentShader->setUniform("pixel_threshold", 0.0001f);
			}
		}

		window.clear();
		window.draw(bg, currentShader);
		window.draw(bg2, currentShader);
		window.draw(bg3, currentShader);
		window.draw(titleText);
		window.display();
	}

	return 0;
}