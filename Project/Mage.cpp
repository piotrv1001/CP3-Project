#include "Mage.h"

Mage::Mage()
{
	HP = 30;
}
Mage::~Mage()
{
	HP = 0;
}
void Mage::HeroAbility(Hero& obj)
{
	if (this->HP <= 28)
		this->HP += 2;
	if (this->HP == 29)
		this->HP += 1;
}
