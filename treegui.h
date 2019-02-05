#ifndef TREEGUI_H
#define TREEGUI_H
#include <SFML/Graphics.hpp>
#include <string_view>
#include <memory>
#include <unordered_map>
#include <vector>

class NodeGUI
{
public:
	static sf::Font font;
	static bool someOneGrabed;
	static std::vector< std::shared_ptr<NodeGUI> >* allNodes;
	std::vector< std::shared_ptr<NodeGUI> > exitEvent;
	// -1  means that exit is vacant
	// in another way, it means order of exitEvent
	std::unordered_map<std::wstring, int> exits;
	sf::RectangleShape rectangle;

	void draw (sf::RenderWindow& window);
	bool addExitEvent (int x, int y);
	NodeGUI ();
	NodeGUI (const std::wstring& name);
	NodeGUI (int x, int y);
	NodeGUI (const std::wstring& name, int x, int y);
	~NodeGUI ();
private:
	sf::Text name;
	bool itWasGrabed = false;
	void update ();//sf::RenderWindow& window);
	void drawSplineInBetweansOfEvents (sf::RenderWindow& window);
};


class TreeGUI
{
public:
	std::vector< std::shared_ptr<NodeGUI> > nodes;
	void draw (sf::RenderWindow& window, std::string& nameOfTheWindow);
	void addNode ();
	void addNode (int x, int y);
	void addNode (const std::wstring& name);
	void addNode (const std::wstring& name, int x, int y);
	TreeGUI ();
	~TreeGUI ();
private:
	int wheelBuff = 0;
	int numWheel = 0;
	bool someOneWasSelected = false;
	bool requireTimeUp = false;
	NodeGUI* selected = nullptr;
	void update (sf::RenderWindow& window, std::string& nameOfTheWindow);
	void selectNodeToGrowIt ();
	void getWheelToControlNameOfExit ();
	void chooseAndGrowNode ();
	void feedBackWhenNodeSelected (sf::RenderWindow& window);
	void feedBackExitSelected (sf::RenderWindow& window);
};

#endif // TREEGUI_H
