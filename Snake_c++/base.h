#ifndef BASE_H
#define BASE_H

#include <string>
#include <map>

namespace ed
{
    enum class Key
	{
		ENTER,
		ESCAPE,
		UP,
		LEFT,
		RIGHT,
		DOWN,
		SAVE,
		UNUSED
    };

	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	enum class ItemMenu
	{
		START,
		SCOREBOARD,
		LOAD,
		HELP,
		EXIT
	};

	// reference jako parametr funkce a jako navratova hodnota
	// pretezovani operatoru
	inline ItemMenu& operator++(ItemMenu& item)
	{
		switch (item)
		{
			case ItemMenu::START:
			{
				return item = ItemMenu::SCOREBOARD;
			}
			case ItemMenu::SCOREBOARD:
			{
				return item = ItemMenu::LOAD; 
			}
			case ItemMenu::LOAD:
			{
				return item = ItemMenu::HELP;
			}
			case ItemMenu::HELP:
			{
				return item = ItemMenu::EXIT;
			}
			case ItemMenu::EXIT:
			{
				return item = ItemMenu::START;
			}

			default: throw std::exception("Unknown type");
		}
	}

	// reference jako parametr funkce a jako navratova hodnota
	// pretezovani operatoru
	inline ItemMenu& operator--(ItemMenu& item)
	{
		switch (item)
		{
			case ItemMenu::START:
			{
				return item = ItemMenu::EXIT;
			}
			case ItemMenu::SCOREBOARD:
			{
				return item = ItemMenu::START;
			}
			case ItemMenu::LOAD:
			{
				return item = ItemMenu::SCOREBOARD;
			}
			case ItemMenu::HELP:
			{
				return item = ItemMenu::LOAD;
			}
			case ItemMenu::EXIT: 
			{
				return item = ItemMenu::HELP;
			}

			default: throw std::exception("Unknown type");
		}
	}

	// STL kontajner
	const std::map<ItemMenu, std::string> ItemMenuToStringMap =
	{
		{ ItemMenu::START, "Start" },
		{ ItemMenu::SCOREBOARD, "Scoreboard" },
		{ ItemMenu::LOAD, "Load" },
		{ ItemMenu::HELP, "Help" },
		{ ItemMenu::EXIT, "Exit" }
	};

	// STL kontajner
	const std::map<int, Key> AllowedKeys =
	{
		{ 13, Key::ENTER },
		{ 27, Key::ESCAPE },
		{ 72, Key::UP },
		{ 75, Key::LEFT },
		{ 77, Key::RIGHT },
		{ 80, Key::DOWN },
		{ 115, Key::SAVE },
	};

	const std::map<Key, Direction> KeyToDirection =
	{ 
		{ Key::UP, Direction::UP },
		{ Key::LEFT, Direction::LEFT },
		{ Key::RIGHT, Direction::RIGHT },
		{ Key::DOWN, Direction::DOWN }
	};
	
	struct Vec2
	{
		int x;
		int y;

		Vec2(int x, int y) : x(x), y(y) {}
    };

	// pretezovani operatoru
	inline bool operator==(const Vec2& left, const Vec2& right)
	{
		return left.x == right.x && left.y == right.y;
	}

	// pretezovani operatoru
	inline bool operator!=(const Vec2& left, const Vec2& right)
	{
		return left.x != right.x || left.y != right.y;
	}

	const int MAX_COLUMNS = 80;
	const int MAX_LINES = 20;

	const int SMALL_FOOD_POINTS = 1;
	const int BIG_FOOD_POINTS = 2;

	const int BIG_FOOD_FREQUENCY = 9;

	// in frames
	const int TEMPORARY_FOOD_FREQUENCY = 120;
	const int TEMPORARY_FOOD_LIFETIME = 60;
	
	const int TEMPORARY_FOOD_POINTS = 5;
}

#endif