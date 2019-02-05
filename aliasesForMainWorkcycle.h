#ifndef ALIASESFORMAINWORKCYCLE_H
#define ALIASESFORMAINWORKCYCLE_H
#include "mousegui.h"
#include "timegui.h"
#include "treegui.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <SFML/Graphics.hpp>

void controlView (sf::View& view, sf::RenderWindow& window);
void init (sf::RenderWindow& window, sf::View& view, TreeGUI& tree);
void workOnAllEvents (sf::RenderWindow& window);
int enterMenu (std::string& nameOfTheWindow, std::string& description);

#endif // ALIASESFORMAINWORKCYCLE_H
