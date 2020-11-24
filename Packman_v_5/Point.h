#ifndef POINT_H
#define POINT_H

#include "Sprite.h"

class Level;

class Point :public Sprite
{
public:
	Point(DravEngine *driveEnginePoint, Level *levelPoint, float x, float y,int index);

	void SpriteUpdate(void) override;

	~Point() override;
};

#endif