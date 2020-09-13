#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include "TemporaryFood.h"
#include "Menu.h"
#include "Input.h"
#include "GameOverException.h"
#include "Scoreboard.h"
#include <iostream>
#include <Windows.h>

using namespace ed;
using namespace std;

Game::Game()
{
}

Game::~Game()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
	gameObjects.clear();
}

int Game::play() {
    menu.draw();
	ItemMenu selectedItem = menu.getSelectedItem();
	
	Scoreboard scoreboard{};
	
	// chytame GameOver vyjimku
	try
	{
		switch (selectedItem)
		{
			case ItemMenu::START:
			{
				reset();
				start();
				break;
			}
			case ItemMenu::SCOREBOARD:
			{
				scoreboard.print();
				play();
				break;
			}
			case ItemMenu::LOAD:
			{
				load();
				break;
			}
			case ItemMenu::HELP:
			{
				help();
				play();
				break;
			}
			case ItemMenu::EXIT: 
			{
				exit(0);
			}
			
			default: break;
		}
	}
	catch (GameOverException& ex)
	{
		system("cls");
		cout << "\033[32m" << ex.what() << "\033[0m" << endl;

		const Snake* snake = ex.getSnake();
		Scoreboard scoreboard{};
		scoreboard.save(snake->getPoints(), snake->getLength());

		//reset();
		play();
	}
    return 0;
}

void Game::help()
{
	system("cls");

	cout << "\033[32m";
	cout << "Welcome to the Snake Game!\n";
	cout << "\n";
	cout << "*** Game Controls ***\n";
	cout << "To move use arrow keys\n";
	cout << "To save the game press 'S' key\n\n";
	cout << "*** Symbols in the game ***\n";
	cout << "0> - that's your snake moving in right direction\n";
	cout << "* - normal food\n";
	cout << "@ - temporary food that will disappear in some time, extra points\n";
	cout << "For normal food you will get 1 point\n";
	cout << "For temporary food you will get 5 points\n";
	cout << "For every 10th food you will get 2 points\n";
	cout << endl;

	system("pause");
	cout << "\033[0m";
}

void Game::reset()
{
	clear();
	initialize();
}

void Game::initialize()
{
	gameObjects.push_back(new Snake(2, Direction::LEFT, { MAX_COLUMNS / 2, MAX_LINES / 2 }));
	gameObjects.push_back(new Food());
	gameObjects.push_back(new TemporaryFood());
}

void Game::clear()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}

	gameObjects.clear();
}

void Game::start()
{
	while (true)
	{
		Key key = input.read();
		if (key == Key::SAVE)
		{
			saveAndExit();
		}
		
		for (unsigned int i = 0; i < gameObjects.size(); ++i)
		{
			gameObjects[i]->update(key, gameObjects);
		}

		system("cls");
		renderer.draw(gameObjects);
		Sleep(10);
	}

	system("pause");
}

void Game::saveAndExit()
{
	cout << "\033[32m" << "Enter file name: ";
	string fileName;
	cin >> fileName;

	ofstream file(fileName, std::ios::out | std::ios::ate);
	if (!file.is_open())
	{
		cout << "\033[32m" << "Unable to open file: " << fileName << "\033[0m" << endl;
		exit(1);
	}
	cout << "\033[0m";
	
	for (unsigned int i = 0; i < gameObjects.size(); ++i)
	{
		if (dynamic_cast<SnakePart*>(gameObjects[i]) != nullptr)
		{
			continue;
		}
		file << gameObjects[i]->serialize();
		file << "\n";
	}

	file.close();

	reset();
	play();
}

void Game::load()
{
	cout << "\033[32m" << "Enter file name: ";
	string fileName;
	cin >> fileName;
	cout << "\033[0m";

	ifstream file(fileName, std::ios::in);
	if (!file.is_open())
	{
		cout << "\033[32m" << "Unable to open file: " << fileName << "\033[0m" << endl;
		system("pause");
		reset();
		play();
		//exit(1);
	}

	clear();

	string str;
	while (getline(file, str))
	{
		size_t typeEndPos = str.find(':');
		string type = str.substr(0, typeEndPos);
		cout << "Deserialize type: " << type << endl;

		if (type == "Snake")
		{
			Snake* snake = new Snake;
			snake->deserialize(str.substr(typeEndPos + 1));
			gameObjects.push_back(snake);
						
			for (auto part : snake->getParts())
			{
				gameObjects.push_back(part);
			}
		}
		else if (type == "Food")
		{
			Food* food = new Food;
			food->deserialize(str.substr(typeEndPos + 1));
			gameObjects.push_back(food);
		}
		else if (type == "TemporaryFood")
		{
			TemporaryFood* tempFood = new TemporaryFood;
			tempFood->deserialize(str.substr(typeEndPos + 1));
			gameObjects.push_back(tempFood);
		}
	}

	file.close();

	start();
}