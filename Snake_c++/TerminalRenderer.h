#ifndef TERMINAL_RENDERER_H
#define TERMINAL_RENDERER_H

#include "GameObject.h"
#include <vector>

namespace ed
{

struct Symbol
{
	char symbol;
	std::string color;
};

class TerminalRenderer
{
private:
	void resetBoard();

	std::vector<std::vector<Symbol>> board;
public:
	TerminalRenderer();

    void draw(const std::vector<GameObject*>& gameObjects);
};

}

#endif