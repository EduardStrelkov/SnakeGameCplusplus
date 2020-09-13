#ifndef SNAKE_PART_H
#define SNAKE_PART_H

#include "Base.h"
#include "GameObject.h"
#include "TerminalGraphicObject.h"

namespace ed
{

class SnakePart : public GameObject, public TerminalGraphicObject
{
public:
	// reference jako parametr funkce
	SnakePart(const Vec2& position) : GameObject(position) {}
	// reference jako parametr funkce
	virtual void update(Key, std::vector<GameObject*>&) override {}

	// reference jako parametr funkce
	void setPosition(const Vec2& pos)
	{
		position.x = pos.x;
		position.y = pos.y;
	}

	virtual char getObjectCharacter() const override
	{
		return 'X';
	}
	
	virtual std::string getObjectColor() const override
	{
		return "\033[32m";
	}
};

}

#endif