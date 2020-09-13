#ifndef GAME_OVER_EXCEPTION_H
#define GAME_OVER_EXCEPTION_H

#include "Snake.h"

#include <exception>
#include <string>

namespace ed
{

class GameOverException : public std::exception
{
public:
	GameOverException(const Snake* snake) : snake(snake) {}

	const char* what() const
	{
		return "GAME OVER"; 
	}
	const Snake* getSnake() const
	{
		return snake;
	}

private:
	const Snake* snake;
};

}

#endif