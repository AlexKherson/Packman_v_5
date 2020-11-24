#include "Point.h"

Point::Point(DravEngine * dravEnginePoint, Level * levelPoint, float x, float y,int index):
	Sprite(dravEnginePoint, levelPoint, x, y,index )
{
	//isEatingPoint = false;
	//basePoint.push_back(*this);
}

void Point::SpriteUpdate(void)
{
	//cout  << pos.x << "\t" << pos.y << "\n";
	addSpriteBufer();
	/*if (!levelSprite->coincidencePointEnemy(pos))
		addSpriteBufer();*/

	/*if (levelSprite->getPosPlayer() == pos)
		isEatingPoint = true;*/
		//levelSprite->delSprite(pos);
	//cout << "point update" << "\n";
}

Point::~Point()
{
}
