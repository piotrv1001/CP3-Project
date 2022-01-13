#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"
class Ice:public Card
{
public:
	Ice(int ad, int hp, int tokens, sf::Sprite sprite);
	~Ice();
	void Passive();
};

