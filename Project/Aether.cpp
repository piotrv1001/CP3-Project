#include "Aether.h"

Aether::Aether(int ad, int hp, int tokens, sf::Sprite sprite)
{
	this->ad = ad;
	this->hp = hp;
	this->tokens = tokens;
	this->sprite = sprite;
	this->Passive();
	this->id = 3;
}

void Aether::Passive()
{
	this->ad += 1;
	this->hp += 1;
}