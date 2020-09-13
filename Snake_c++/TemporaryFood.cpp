#include "TemporaryFood.h"

using namespace ed;
using namespace std;

TemporaryFood::TemporaryFood() : appearanceCounter(0), lifetimeCounter(0), visible(false) {}

int TemporaryFood::eat()
{
	if (!visible)
	{
		return 0;
	}

	randomPosition();
	visible = false;
	appearanceCounter = 0;
	lifetimeCounter = 0;

	return TEMPORARY_FOOD_POINTS;
}

char TemporaryFood::getObjectCharacter() const
{
	return visible ? '@' : ' ';
}

void TemporaryFood::update(Key, vector<GameObject*>&)
{
	if (!visible)
	{
		appearanceCounter++;
		if (appearanceCounter >= TEMPORARY_FOOD_FREQUENCY)
		{
			appearanceCounter = 0;
			visible = true;
		}
	}
	else
	{
		lifetimeCounter++;
		if (lifetimeCounter >= TEMPORARY_FOOD_LIFETIME)
		{
			lifetimeCounter = 0;
			visible = false;
		}
	}
}

std::string TemporaryFood::serialize()
{
	return "TemporaryFood:appearanceCounter:" + to_string(appearanceCounter) + ":lifetimeCounter:" + to_string(lifetimeCounter) +
		":visible:" + to_string(visible) + GameObject::serialize();
}

void TemporaryFood::deserialize(const string& str)
{
	// appearanceCounter:56:lifetimeCounter:0:visible:0:pos:19,6
	size_t appearanceCounterEndPos = str.find(':', 18);
	appearanceCounter = stoi(str.substr(18, appearanceCounterEndPos - 18));
	
	size_t lifetimeCounterEndPos = str.find(':', appearanceCounterEndPos + 17);
	lifetimeCounter = stoi(str.substr(appearanceCounterEndPos + 17, lifetimeCounterEndPos - appearanceCounterEndPos + 17));

	size_t visibleEndPos = str.find(':', lifetimeCounterEndPos + 9);
	lifetimeCounter = stoi(str.substr(lifetimeCounterEndPos + 9, visibleEndPos - lifetimeCounterEndPos + 9));

	string pos = str.substr(visibleEndPos);
	GameObject::deserialize(pos);
}

std::string TemporaryFood::getObjectColor() const
{
	return "\033[33m";
}