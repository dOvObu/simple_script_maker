#include "mousegui.h"
#include "timegui.h"
#include "treegui.h"
#include "aliasesForMainWorkcycle.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdio>
#include <conio.h>


//-------------------------------------------------------------------------//


int main ()
{
	setlocale (LC_ALL, "Russian");
	std::string nameOfTheWindow, description;
	if (!enterMenu (nameOfTheWindow, description)) return 0;
	std::cout << description << std::endl;
	sf::RenderWindow window (sf::VideoMode (2*400, 2*300), nameOfTheWindow.c_str());
	sf::View view;
	TreeGUI tree;
	init (window, view, tree);

	while (window.isOpen ())
	{
		workOnAllEvents (window);
		controlView (view, window);

		window.setView (view);
		window.clear ();
		tree.draw (window, nameOfTheWindow);
		window.display ();
	}

	return 0;
}
