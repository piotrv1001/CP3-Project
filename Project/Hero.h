#pragma once
class Hero
{
public:
	int HP;
	bool clicked = false;
	virtual void HeroAbility(Hero& obj)=0;
};

