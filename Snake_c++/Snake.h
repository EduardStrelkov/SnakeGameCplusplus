#ifndef SNAKE_H
#define SNAKE_H

#include "SnakePart.h"
#include "Base.h"
#include "GameObject.h"
#include "TerminalGraphicObject.h"

#include <vector>

namespace ed
{

// dedicnost
class Snake : public GameObject, public TerminalGraphicObject
{
private:
    Direction direction;
    std::vector<SnakePart*> parts;
	int length;
	bool initialized;
	int points;

	Vec2 prevTailPosition;
	
	void initialize(std::vector<GameObject*>& gameObjects);

	void move();
	void eatFood(std::vector<GameObject*>& gameObjects);
	bool checkCollision() const;

	void log(const std::string& info);

	// pretezovani operatoru
	friend std::ostream& operator<<(std::ostream& out, const Snake& snake);

	// pretezovani funkci
	void update(Key key);

public:
	// bezparametricky konstruktor
	Snake();

	Snake(int length_, Direction direction_, const Vec2& initPos_);

	inline std::vector<SnakePart*> getParts() const
	{
		return parts;
	}

	// pretezovani funkci viz update(Key key)
	virtual void update(Key key, std::vector<GameObject*>& gameObjects) override;

	virtual std::string getObjectInformation() const override;
	virtual char getObjectCharacter() const override;
	virtual std::string getObjectColor() const override;

	inline int getPoints() const
	{
		return points;
	}

	inline int getLength() const
	{
		return length;
	}

	virtual std::string serialize() override;
	virtual void deserialize(const std::string& str) override;
};

}

#endif