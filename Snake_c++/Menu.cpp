#include "Menu.h"
#include "base.h"
#include <iostream>
#include <conio.h>

using namespace ed;
using namespace std;

Menu::Menu() : selectedItem(ItemMenu::START) {}

void Menu::draw()
{
	system("CLS");
    do
	{
		// print menu items
        for (ItemMenu item = ItemMenu::START;; ++item)
		{
			cout << "\033[32m";
            if (item == selectedItem)
			{
                cout << "> ";
            }
			else
			{
                cout << "  ";
            }
            cout << ItemMenuToStringMap.at(item) << '\n';
			cout << "\033[0m";

			if (item == ItemMenu::EXIT)
			{
				break;
			}
        }

		if (processInput())
		{
			break;
		}

		// clear screen
		system("CLS");
	} while (true);
}

bool Menu::processInput()
{
	int input = _getch();

	Key key;
	try
	{
		key = AllowedKeys.at(input);
	}
	catch (const std::out_of_range&)
	{
		// ignore other keys
		return false;
	}

	switch (key)
	{
		case Key::UP:
		{
			--selectedItem;
			break;
		}
		case Key::DOWN:
		{
			++selectedItem;
			break;
		}
		case Key::ENTER:
		{
			return true;
		}
		
		default: break;
	}

	return false;
}