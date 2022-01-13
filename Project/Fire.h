#pragma once
#include "Card.h"
#include <SFML/Graphics.hpp>
class Fire: public Card
{
public:
	Fire(int ad, int hp, int tokens, sf::Sprite sprite);
	~Fire();
	void Passive();
};

