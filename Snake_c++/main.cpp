#include "Game.h"

int main(int argc, char** argv)
{
	ed::Game* game = new ed::Game;
	int result = game->play();
	delete game;
	return result;
}