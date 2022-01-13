#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"
class Aether :public Card
{
public:
	Aether(int ad, int hp, int tokens, sf::Sprite sprite);
	~Aether();
	void Passive();
};
