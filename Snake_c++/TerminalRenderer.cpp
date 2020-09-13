#include "TerminalRenderer.h"
#include "TerminalGraphicObject.h"
#include "Snake.h"
#include "SnakePart.h"
#include "Food.h"

#include <iostream>

using namespace ed;
using namespace std;

TerminalRenderer::TerminalRenderer()
{
	board = vector<vector<Symbol>>(MAX_COLUMNS, vector<Symbol>(MAX_LINES));
}

void TerminalRenderer::resetBoard()
{
	for (int y = 0; y < MAX_LINES; y++)
	{
		for (int x = 0; x < MAX_COLUMNS; x++)
		{
			if (x == 0 || y == 0 || x == MAX_COLUMNS - 1 || y == MAX_LINES - 1)
			{
				board[x][y].symbol = char(178);
				board[x][y].color = "\033[42m";
			}
			else
			{
				board[x][y].symbol = ' ';
			}
		}
	}
}

// reference jako parametr funkce
void TerminalRenderer::draw(const vector<GameObject*>& gameObjects)
{
	resetBoard();
	// iterator
	for (auto gameObject = gameObjects.begin(); gameObject != gameObjects.end(); ++gameObject)
	{
		Vec2 position = (*gameObject)->getPosition();

		TerminalGraphicObject* graphicObject = dynamic_cast<TerminalGraphicObject*>(*gameObject);
		if (graphicObject != nullptr)
		{
			board[position.x][position.y].symbol = graphicObject->getObjectCharacter();
			board[position.x][position.y].color = graphicObject->getObjectColor();
			std::string objectInformation = graphicObject->getObjectInformation();
			cout << "\033[32m" << objectInformation << "\033[0m";
			if (!objectInformation.empty())
			{
				cout << endl;
			}
		}
	}

	for (int y = 0; y < MAX_LINES; y++)
	{
		for (int x = 0; x < MAX_COLUMNS; x++)
		{
			cout << board[x][y].color << board[x][y].symbol << "\033[0m";
		}
		cout << endl;
	}
}