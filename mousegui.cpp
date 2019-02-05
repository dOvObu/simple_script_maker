#include "mousegui.h"
#include <iostream>

std::vector<std::function<void(int)> > MouseGui::wheelFuncs;
sf::RenderWindow* MouseGui::window = nullptr;
int MouseGui::wheel = 16777200;


sf::Vector2f MouseGui::getPosition ()
{
	sf::Vector2f size (window->getView ().getSize ());
	sf::Vector2f centerPos (window->getView ().getCenter ());
	sf::Vector2f mpos (sf::Mouse::getPosition (*window));
	float zoom = size.x / window->getSize().x;
	return zoom * mpos + centerPos - size * 0.5f;
}
