#include "Character.h"

Character::Character(DravEngine * dravEngineCharacter, Level *levelCharacter, float x, float y,int index,
	int lives,char up, char rigth, char down, char left):
	Sprite(dravEngineCharacter,levelCharacter, x, y,index /*,classCharacter*/)
{
	

	this->up = up;
	this->rigth = rigth;
	this->down = down;
	this->left = left;

	this->lives = lives;
	
}

Character::~Character()
{

}

bool Character::pressKey( char & key)
{
	prevPos = pos;
	if (key == up)
	{
		
		if (isValiedLevelMove((int)(pos.x - 1),(int) pos.y))
		{
			image = baseImageCharacter[dir_up];
			moveSprite(-1, 0);
			return true;
		}

	}
	if (key == rigth)
	{
		if (pos.x == 11 && pos.y == dravEngineSprite->get_screenWidth() - 1)
			pos.y = -1;

		if (isValiedLevelMove((int)pos.x, (int)(pos.y + 1)))
		{
			image = baseImageCharacter[dir_rigth];

			moveSprite(0, 1);
			return true;
		}
	}
		

	if (key == down)
	{
		if ((pos.x + 1) == 10 && pos.y == 13)
			return false;
		if (isValiedLevelMove((int)(pos.x + 1), (int)pos.y))
		{
			image = baseImageCharacter[dir_down];
			moveSprite(1, 0);
			return true;
		}
	}
		

	if (key == left)
	{
		if (pos.x == 11 && pos.y == 0)
			pos.y = dravEngineSprite->get_screenWidth();

		if (isValiedLevelMove((int)pos.x, (int)(pos.y - 1)))
		{
			image = baseImageCharacter[dir_left];

			moveSprite(0, -1);
			return true;
		}
	}
		
	return false;
}

bool Character::isAlives(void)
{
	return --lives==0;
}

int Character::getLives(void) const
{
	return lives;
}

Coordinates & Character::getPosCharacter(void)
{
	return pos;
}
