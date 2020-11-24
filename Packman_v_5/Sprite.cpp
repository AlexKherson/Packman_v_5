#include "Sprite.h"






Sprite::Sprite(DravEngine * dravEngineSprite,Level *levelSprite, float x, float y,int index/*,int classId*/)
{
	this->dravEngineSprite = dravEngineSprite;
	this->levelSprite = levelSprite;

	pos.x = x;
	pos.y = y;

	prevPos = pos;

	if (index < 0 && index>8)
		throw std::exception();

	this->image = baseImage[index] ;
	this->color = baseColor[index] ;

	classId = index;
	

	
}

Sprite::~Sprite()
{
	
}

void Sprite::addSpriteBufer(void) const
{
	dravEngineSprite->changeBufer((int)pos.x,(int) pos.y, image, color);
}

int Sprite::getClassId(void) const
{
	return classId;
}

Coordinates Sprite::getPos(void) const
{
	return pos;
}

void Sprite::SpriteUpdate(void)
{
	
}

bool Sprite::isValiedLevelMove(const int x, const int y)
{
	return levelSprite->get_levelMap()[x][y]!='0';
}

void Sprite::moveSprite(const int shiftX, const int shiftY)
{
	pos.x += (float)(1 * shiftX);
	pos.y += (float)(1 * shiftY);
	if (!levelSprite->isValiedErase(prevPos))
		eraseSprite((int)prevPos.x, (int)prevPos.y);
	addSpriteBufer();
	
}

void Sprite::eraseSprite(const int x, const int y)
{
	dravEngineSprite->changeBufer(x, y, ' ', 8);
}
