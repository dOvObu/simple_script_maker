#ifndef MOUSEGUI_H
#define MOUSEGUI_H
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class MouseGui
{
public:
	static std::vector<std::function<void(int)> > wheelFuncs;
	static sf::Vector2f getPosition ();
	static sf::RenderWindow* window;
	static int wheel;
};

#endif // MOUSEGUI_H
