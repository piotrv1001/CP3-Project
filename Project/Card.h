#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
class Card
{
public:
	int ad, hp, tokens, id;
	sf::Sprite sprite;
	bool hovered = false;
	bool clicked = false;
	bool movable = true;
	bool attackable = true;
	virtual void Passive()=0;
	void DisplayStats(sf::RenderWindow& window);
};

