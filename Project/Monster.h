#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Monster
{
public:
	int ad, hp, key;
	sf::Sprite sprite;
	Monster(int ad, int hp, int key, sf::Sprite sprite);
	void Display(sf::RenderWindow& window);
};

