#pragma once
#include "Hero.h"
class Hunter:public Hero
{
public:
	Hunter();
	~Hunter();
	void HeroAbility(Hero& obj);
};

