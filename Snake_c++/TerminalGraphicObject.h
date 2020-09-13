#ifndef TERMINAL_GRAPHIC_OBJECT_H
#define TERMINAL_GRAPHIC_OBJECT_H

#include <string>
// prostory jmen
namespace ed
{
// Abstraktni trida protoze ma pure virtual function
class TerminalGraphicObject
{
public:
	// virtual function
	virtual std::string getObjectInformation() const
	{
		return std::string();
	}
	// pure virtual function
	virtual char getObjectCharacter() const = 0;

	virtual std::string getObjectColor() const
	{
		return "\033[0m";
	}
};

}

#endif