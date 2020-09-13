#ifndef MENU_H
#define MENU_H

#include "base.h"

namespace ed
{

class Menu
{
private:
	ItemMenu selectedItem;

	bool processInput();
public:
	// bezparametricky konstruktor
    Menu();
    void draw();

	inline ItemMenu getSelectedItem()
	{
		return selectedItem;
	}
};

}

#endif