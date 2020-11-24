#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"

enum baseDirectCharacter
{
	dir_up,
	dir_rigth,
	dir_down,
	dir_left
};

class Character :public Sprite
{
public:
	Character( DravEngine *dravEngineCharacter,Level *levelCharacter, float x, float y,int index,
		int lives,char up = '5', char rigth = '3', char down = '2', char left = '1');
	~Character() override;

public:
	bool pressKey( char &key);

	bool isAlives(void);

	int getLives(void) const;

	Coordinates & getPosCharacter(void);

private:
	char up;
	char rigth;
	char down;
	char left;

	int lives;

	const char baseImageCharacter[4] = { 'v','<','^','>' };
};

#endif
