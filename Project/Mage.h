#pragma once
#include "Hero.h"
class Mage:public Hero
{
public:
	Mage();
	~Mage();
	void HeroAbility(Hero& obj);
};

