#include "Snake.h"
#include "Food.h"
#include "GameOverException.h"
#include <fstream>
#include <iostream>

#include <string>

using namespace std;

namespace ed
{

Snake::Snake() : GameObject({0,0}), direction(Direction::DOWN), length(0), initialized(false), points(0), prevTailPosition(0, 0) {}

Snake::Snake(int length, Direction direction, const Vec2& initPos_)
    : GameObject(initPos_), direction(direction), length(length), initialized(false), points(0), prevTailPosition(0, 0) {}

// pretezovani operatoru
std::ostream& operator<<(std::ostream& out, const Snake& snake)
{
	out << "SNAKE: {direction: " << static_cast<int>(snake.direction) << ", position: {\n";
	out << "[" << snake.position.x << ", " << snake.position.y << "],";
	out << " parts: {\n";

	for (int i = 0; i < snake.length; i++)
	{
		out << i << ": " << "[" << snake.parts[i]->getPosition().x << ", " << snake.parts[i]->getPosition().y << "]\n";
	}
	out << "}}" << endl;

	return out;
}

//posun
// reference jako parametr funkce
void Snake::update(Key key, vector<GameObject*>& gameObjects)
{
	if (!initialized)
	{
		initialize(gameObjects);
	}

	update(key);
	move();
	eatFood(gameObjects);
	
	if (!checkCollision())
	{
		// vyhazovani GameOverException
		throw GameOverException(this);
	}
}

// reference jako parametr funkce
void Snake::initialize(vector<GameObject*>& gameObjects)
{
	Vec2 newPosition = position;
	for (int i = 0; i < length; i++)
	{
		newPosition.x++;
		SnakePart* snakePart = new SnakePart(newPosition);
		parts.push_back(snakePart);
		gameObjects.push_back(snakePart);
	}

	initialized = true;
}

//smer 
void Snake::update(Key key) 
{
	Direction new_direction = direction;
	// vyjimka
	try
	{
		new_direction = KeyToDirection.at(key);
	}
	catch (const std::out_of_range&)
	{
		// ignore other keys
		return;
	}

	switch (new_direction)
	{
		case Direction::UP:
		{
			if (direction == Direction::DOWN)
			{
				return;
			}
			break;
		}
		case Direction::DOWN:
		{
			if (direction == Direction::UP)
			{
				return;
			}
			break;
		}
		case Direction::LEFT:
		{
			if (direction == Direction::RIGHT)
			{
				return;
			}
			break;
		}
		case Direction::RIGHT:
		{
			if (direction == Direction::LEFT)
			{
				return;
			}
			break;
		}

		default: break;
	}
	direction = new_direction;
}

// reference jako parametr funkce
void Snake::log(const std::string& info)
{
	std::ofstream logger("SnakeLog.txt", std::ios::out | std::ios::app);
	logger << info << "\n";
	logger << *this << endl;
	logger.close();
}

void Snake::move()
{
	log("-------before move-------");
	Vec2 prev_head_position = position;
	switch (direction)
	{
		case Direction::UP:
		{
			position.y--;
			break;
		}
		case Direction::DOWN:
		{
			position.y++;
			break;
		}
		case Direction::LEFT:
		{
			position.x--;
			break;
		}
		case Direction::RIGHT:
		{
			position.x++;
			break;
		}

		default: break;
	}
	
	// Update parts
	size_t size = parts.size();
	
	if (size != 0)
	{
		prevTailPosition = parts[size - 1]->getPosition();
	}

	for (int i = size - 1; i > 0; i--)
	{
		parts[i]->setPosition(parts[i - 1]->getPosition());
	}

	if (size != 0)
	{
		parts[0]->setPosition(prev_head_position);
	}
	/////////////////////

	log("------after move-------");
}

// reference jako parametr funkce
void Snake::eatFood(vector<GameObject*>& gameObjects)
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject->getPosition() != position)
		{
			continue;
		}

		Food* food = dynamic_cast<Food*>(gameObject);
		if (food != nullptr)
		{
			int foodPoints = food->eat();
			if (foodPoints == 0)
			{
				break;
			}
			points += foodPoints;
			SnakePart* snakePart = new SnakePart(prevTailPosition);
			parts.push_back(snakePart);
			gameObjects.push_back(snakePart);
			length++;
			break;
		}
	}
}

bool Snake::checkCollision() const
{
	// Check collision with snake parts
	for (size_t i = 0; i < parts.size(); i++)
	{
		if (position == parts[i]->getPosition())
		{
			return false;
		}
	}

	// Check wall collisions
	return position.x != 0 && position.x != MAX_COLUMNS - 1 && position.y != 0 && position.y != MAX_LINES - 1;
}

std::string Snake::getObjectInformation() const
{
	return "Points: " + to_string(points) + " | Length: " + to_string(length + 1);
}

char Snake::getObjectCharacter() const
{
	switch (direction)
	{
		case Direction::UP:
		{
			return '^';
		}
		case Direction::DOWN:
		{
			return 'v';
		}
		case Direction::LEFT:
		{
			return '<';
		}
		case Direction::RIGHT:
		{
			return '>';
		}

		default: return ' ';
	}
}

std::string Snake::serialize()
{
	string result = "Snake:direction:" + to_string(static_cast<int>(direction)) + ":length:" + to_string(length) +
		":initialized:" + to_string(initialized) + ":points:" + to_string(points) +
		":prevTailPosition:" + to_string(prevTailPosition.x) + "," + to_string(prevTailPosition.y) + ":parts";

	for (int i = 0; i < length; i++)
	{
		result += parts[i]->serialize() + "&";
	}

	result += "|" + GameObject::serialize();
	return result;
}

void Snake::deserialize(const string& str)
{
	// direction:3:length:3:initialized:1:points:1:prevTailPosition:47,3:parts:pos:48,1&:pos:47,1&:pos:47,2&|:pos:49,1
	size_t directionEndPos = str.find(':', 10);
	direction = static_cast<Direction>(stoi(str.substr(10, directionEndPos - 10)));

	size_t lengthEndPos = str.find(':', directionEndPos + 8);
	length = stoi(str.substr(directionEndPos + 8, lengthEndPos - directionEndPos + 8));

	size_t initializedEndPos = str.find(':', lengthEndPos + 13);
	initialized = stoi(str.substr(lengthEndPos + 13, initializedEndPos - lengthEndPos + 13));

	size_t pointsEndPos = str.find(':', initializedEndPos + 8);
	points = stoi(str.substr(initializedEndPos + 8, pointsEndPos - initializedEndPos + 8));

	size_t prevTailPosEndPos = str.find(':', pointsEndPos + 18);
	
	size_t commaPos = str.find(',', pointsEndPos + 18);
	prevTailPosition.x = stoi(str.substr(pointsEndPos + 18, commaPos - pointsEndPos + 18));
	prevTailPosition.y = stoi(str.substr(commaPos + 1, prevTailPosEndPos - commaPos - 1));

	size_t partsStartPos = prevTailPosEndPos + 6;
	size_t partsEndPos = str.find('|', partsStartPos);
	
	//:pos:67,12&:pos:66,12&:pos:65,12&:pos:65,11&
	string partsStr = str.substr(partsStartPos, partsEndPos - partsStartPos);
	
	size_t partStartPos = 0;
	for (int i = 0; i < length; i++)
	{
		SnakePart* snakePart = new SnakePart({ 0, 0 });
		//:pos:48,1
		size_t partEnd = partsStr.find('&', partStartPos);
		string partStr = partsStr.substr(partStartPos, partEnd - partStartPos);
		snakePart->deserialize(partStr);
		parts.push_back(snakePart);
	}

	string pos = str.substr(partsEndPos + 1);
	GameObject::deserialize(pos);
}

std::string Snake::getObjectColor() const
{
	return "\033[32m";
}

} // namespace ed