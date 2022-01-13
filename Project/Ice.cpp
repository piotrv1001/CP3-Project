#include "Ice.h"

Ice::Ice(int ad, int hp, int tokens, sf::Sprite sprite)
{
	this->ad = ad;
	this->hp = hp;
	this->tokens = tokens;
	this->sprite = sprite;
	this->Passive();
	this->id = 2;
}

void Ice::Passive()
{
	this->hp += 2;
}