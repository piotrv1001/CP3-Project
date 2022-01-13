#include "Fire.h"

Fire::Fire(int ad, int hp, int tokens, sf::Sprite sprite)
{
	this->ad = ad;
	this->hp = hp;
	this->tokens = tokens;
	this->sprite = sprite;
	this->Passive();
	this->id = 1;
}

void Fire::Passive()
{
	this->ad += 2;
}