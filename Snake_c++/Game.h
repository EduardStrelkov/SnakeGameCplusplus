#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "Input.h"
#include "Snake.h"
#include "GameObject.h"
#include "TerminalRenderer.h"

#include <vector>

// prostory jmen
namespace ed
{
class Game
{
public:
	// bezparametricky konstruktor
	Game();
	// destruktor
	~Game();
	int play();

private:
    Menu menu;
    Input input;
	TerminalRenderer renderer;

	// STL kontajner
	std::vector<GameObject*> gameObjects;

	void start();

	void reset();
	void initialize();
	void clear();

	void saveAndExit();

	void load();
	void help();
};

}

#endif