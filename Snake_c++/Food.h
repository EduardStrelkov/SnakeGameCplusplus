#ifndef FOOD_H
#define FOOD_H

#include "Base.h"
#include "GameObject.h"
#include "TerminalGraphicObject.h"
#include <random>

namespace ed
{
// dedicnost
class Food : public GameObject, public TerminalGraphicObject
{
protected:
	void randomPosition();

private:
	int pointsCounter;
	std::uniform_int_distribution<int> xDistribution;
	std::uniform_int_distribution<int> yDistribution;
public:
	// bezparametricky konstruktor
	Food();

	// virtual function
	virtual int eat();
	
	virtual char getObjectCharacter() const override;
	virtual std::string getObjectColor() const override;
	virtual void update(Key key, std::vector<GameObject*>& gameObjects) {}

	virtual std::string serialize() override;
	virtual void deserialize(const std::string& str) override;
};

}

#endif