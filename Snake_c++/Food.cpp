#include "Food.h"
#include <random>

using namespace ed;
using namespace std;

Food::Food() : GameObject({ 0, 0 }), pointsCounter(0),
	xDistribution(1, MAX_COLUMNS - 2), yDistribution(1, MAX_LINES - 2)
{	
	randomPosition();
}

void Food::randomPosition()
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	Vec2 newPosition{ xDistribution(generator), yDistribution(generator) };
	while (newPosition == position)
	{
		newPosition = Vec2{ xDistribution(generator), yDistribution(generator) };
	}

	position = newPosition;
}

int Food::eat()
{
	randomPosition();
	if (pointsCounter++ == BIG_FOOD_FREQUENCY)
	{
		pointsCounter = 0;
		return BIG_FOOD_POINTS;
	}
	return SMALL_FOOD_POINTS;
}

char Food::getObjectCharacter() const
{
	return '*';
}

std::string Food::getObjectColor() const
{
	return "\033[31m";
}

string Food::serialize()
{
	return "Food:pointsCounter:" + to_string(pointsCounter) + GameObject::serialize();
}

void Food::deserialize(const string& str)
{
	// pointsCounter:1:pos:15,12
	size_t pointsCounterEndPos = str.find(':', 14);
	pointsCounter = stoi(str.substr(14, pointsCounterEndPos - 14));
	string pos = str.substr(pointsCounterEndPos);
	GameObject::deserialize(pos);
}