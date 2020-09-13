#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "base.h"
#include <vector>
#include <fstream>

namespace ed
{

// Abstraktni trida protoze ma pure virtual function
class GameObject
{
public:
    GameObject(const Vec2& position);
	// pure virtual function
	virtual void update(Key key, std::vector<GameObject*>& gameObjects) = 0;

	virtual void deserialize(const std::string& str);
	virtual std::string serialize();

	// reference jako navratova hodnota
	inline const Vec2& getPosition() const
	{
		return position;
	}

protected:
    Vec2 position;
};

}

#endif