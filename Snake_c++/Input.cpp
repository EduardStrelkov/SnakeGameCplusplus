#include "Input.h"
#include <iostream>
#include <conio.h>

using namespace ed;
using namespace std;

Key Input::read()
{
	if (_kbhit())
	{
		int input = _getch();
		Key key;
		// vyjimka
		try
		{
			key = AllowedKeys.at(input);
		}
		catch (const std::out_of_range&)
		{
			// ignore other keys
			return Key::UNUSED;
		}
		return key;
	}
	return Key::UNUSED;
}