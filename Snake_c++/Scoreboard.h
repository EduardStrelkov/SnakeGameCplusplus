#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>

namespace ed
{

class Scoreboard
{
public:
	void save(int points, int length);
	void print();

private:
	const char* FILE_NAME = "scoreboard.txt";
};

}

#endif