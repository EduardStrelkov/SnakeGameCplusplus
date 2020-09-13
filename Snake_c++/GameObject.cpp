#include "GameObject.h"

using namespace ed;
using namespace std;

GameObject::GameObject(const Vec2& position) : position(position) {}

string GameObject::serialize()
{
	return ":pos:" + to_string(position.x) + "," + to_string(position.y);
}

void GameObject::deserialize(const string& str)
{   //     567
	//:pos:48,1
	size_t commaPos = str.find(',', 4);
	position.x = stoi(str.substr(5, commaPos - 5));
	position.y = stoi(str.substr(commaPos + 1));
}