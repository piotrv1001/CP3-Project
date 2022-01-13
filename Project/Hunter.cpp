#include "Hunter.h"

Hunter::Hunter()
{
	HP = 30;
}
Hunter::~Hunter()
{
	HP = 0;
}
void Hunter::HeroAbility(Hero&obj)
{
	obj.HP -= 2;
}