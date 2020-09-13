#ifndef TEMPORARY_FOOD_H
#define TEMPORARY_FOOD_H

#include "Food.h"

namespace ed 
{
// dedicnost
class TemporaryFood : public Food
{
private:
	int appearanceCounter;
	int lifetimeCounter;
	bool visible;

public:
	// bezparametricky konstruktor
	TemporaryFood();
	virtual int eat() override;
	
	virtual char getObjectCharacter() const override;
	std::string getObjectColor() const override;
	virtual void update(Key key, std::vector<GameObject*>& gameObjects) override;

	virtual std::string serialize() override;
	virtual void deserialize(const std::string& str) override;
};

}

#endif