#include "treegui.h"
#include "mousegui.h"
#include "besiercurve.h"
#include <iostream>




bool NodeGUI::someOneGrabed = false;
std::vector< std::shared_ptr<NodeGUI> >* NodeGUI::allNodes = nullptr;
sf::Font NodeGUI::font = sf::Font ();

void NodeGUI::update ()
{
	if (!sf::Mouse::isButtonPressed (sf::Mouse::Left) && itWasGrabed) {someOneGrabed = itWasGrabed = false;}
	else {
		if (!someOneGrabed) {
			auto pmos = MouseGui::getPosition (), rp1 = rectangle.getPosition ();
			auto rp2 = rectangle.getSize () + rp1;
			if (rp1.x < pmos.x && rp2.x > pmos.x && rp1.y < pmos.y && rp2.y > pmos.y) {someOneGrabed = itWasGrabed = true;}
		}
		else if (itWasGrabed) { rectangle.setPosition (MouseGui::getPosition () - rectangle.getSize () * 0.5f);}
	}
	name.setPosition (rectangle.getPosition ());
	name.setCharacterSize (16);
}

void NodeGUI::drawSplineInBetweansOfEvents (sf::RenderWindow& window)
{
	auto vec = rectangle.getSize ();
	const float shift = 80.f;
	vec.y *= 0.5f;
	vec += rectangle.getPosition ();
	float m[8] = { vec.x, vec.y, vec.x + shift, vec.y, 0.f, 0.f, 0.f, 0.f };
	for (auto& it : exitEvent)
	{
		const auto sz = it->rectangle.getSize ().y * 0.5f;
		const auto v2 = it->rectangle.getPosition ();
		m[6] = v2.x;					m[7] = v2.y + sz;
		m[4] = m[6] - shift;	m[5] = m[7];
		getRealCubicBezierCurve2d( m, 0.01f, [&window](float (&a)[4])
			{
				sf::Vertex v[2] = { sf::Vector2f (a[0], a[1]), sf::Vector2f (a[2], a[3]) };
				window.draw (v,2,sf::LinesStrip);
			});
	}
}

void NodeGUI::draw (sf::RenderWindow& window)
{
	this->update ();//window);
	if (exitEvent.size ()) { drawSplineInBetweansOfEvents (window); }
	window.draw (this->rectangle);
	window.draw (this->name);
}

bool NodeGUI::addExitEvent (int x, int y)
{
	if (!someOneGrabed)
	{
		//auto pmos = MouseGui::getPosition ();
		for (std::shared_ptr<NodeGUI>& it : *allNodes)
		{
			if (it.get () == this) { continue; }
			auto rp1 = it->rectangle.getPosition ();
			auto rp2 = it->rectangle.getSize () + rp1;
			if (rp1.x < x && rp2.x > x && rp1.y < y && rp2.y > y)
			{
				exitEvent.push_back (it);
				return true;
			}
		}
	}
	return false;
}

NodeGUI::NodeGUI ()
{
	this->rectangle.setSize (sf::Vector2f (100, 75));
	this->rectangle.setFillColor (sf::Color::Black);
	this->rectangle.setOutlineThickness (2);
	this->rectangle.setOutlineColor (sf::Color::White);
	this->name.setFont (font);
}

NodeGUI::NodeGUI (const std::wstring& name)
{
	this->rectangle.setSize (sf::Vector2f (100, 75));
	this->rectangle.setFillColor (sf::Color::Black);
	this->rectangle.setOutlineThickness (2);
	this->rectangle.setOutlineColor (sf::Color::White);
	this->name.setString (name);
	this->name.setFont (font);
}

NodeGUI::NodeGUI (int x, int y)
{
	this->rectangle.setPosition (x, y);
	this->rectangle.setSize (sf::Vector2f (100, 75));
	this->rectangle.setFillColor (sf::Color::Black);
	this->rectangle.setOutlineThickness (2);
	this->rectangle.setOutlineColor (sf::Color::White);
	this->name.setFont (font);
}

NodeGUI::NodeGUI (const std::wstring& name, int x, int y)
{
	this->rectangle.setPosition (x, y);
	this->rectangle.setSize (sf::Vector2f (100, 75));
	this->rectangle.setFillColor (sf::Color::Black);
	this->rectangle.setOutlineThickness (2);
	this->rectangle.setOutlineColor (sf::Color::White);
	this->name.setString (name);
	this->name.setFont (font);

	this->exits[L"Сделал полезный инструмент"] = -1;
	this->exits[L"Сделал удобный инструмент"] = -1;
	this->exits[L"Не доделал инструмент"] = -1;
}



NodeGUI::~NodeGUI () {}

TreeGUI::TreeGUI () {NodeGUI::allNodes = &(this->nodes);}

TreeGUI::~TreeGUI () {}

void TreeGUI::getWheelToControlNameOfExit ()
{
	MouseGui::wheelFuncs.push_back ([this](int delta)->void {
		this->wheelBuff += delta;
		if (this->wheelBuff >= static_cast<int> (this->selected->exits.size ())) { this->wheelBuff = 0;}
		if (this->wheelBuff < 0) {this->wheelBuff = static_cast<int> (this->selected->exits.size ()) - 1;}
	});
	numWheel = static_cast<int> (MouseGui::wheelFuncs.size ());
}

void TreeGUI::selectNodeToGrowIt ()
{
	auto pmos = MouseGui::getPosition ();
	for (auto& it : this->nodes)
	{
		auto rp1 = it->rectangle.getPosition ();
		auto rp2 = it->rectangle.getSize () + rp1;
		if (rp1.x < pmos.x && rp2.x > pmos.x && rp1.y < pmos.y && rp2.y > pmos.y && it->exits.size ())
		{
			selected = it.get ();
			if (numWheel == 0) { getWheelToControlNameOfExit (); }
			break;
		}
	}
}

void TreeGUI::chooseAndGrowNode ()
{
	if (!requireTimeUp)
	{
		if (someOneWasSelected && selected != nullptr)
		{
			auto pmos = MouseGui::getPosition ();
			if (selected->addExitEvent (static_cast<int>(pmos.x), static_cast<int>(pmos.y)))
			{
				selected = nullptr;
				someOneWasSelected = false;
				requireTimeUp = true;
				if (numWheel)
				{
					MouseGui::wheelFuncs.erase (std::begin (MouseGui::wheelFuncs) + numWheel - 1);
					wheelBuff = numWheel = 0;
				}
			}
		}
		else {selectNodeToGrowIt ();}
	}
}

void TreeGUI::feedBackWhenNodeSelected (sf::RenderWindow& window)
{
	auto rpos = selected->rectangle.getPosition ();
	auto rsize = selected->rectangle.getSize () * 0.5f;
	rpos += rsize;
	sf::Vertex v[] = {
		sf::Vector2f (rpos.x + rsize.x, rpos.y),
		sf::Vector2f (rpos.x + rsize.x + 30.f, rpos.y),
		MouseGui::getPosition ()
	};
	window.draw (v, 3, sf::LinesStrip);
}

void TreeGUI::feedBackExitSelected (sf::RenderWindow& window)
{
	sf::Text str;
	auto it = std::begin (selected->exits);
	for (int i = 0; i < wheelBuff; ++i, ++it){}
	str.setString (it->first);
	str.setFont (NodeGUI::font);
	str.setCharacterSize (14);
	str.setPosition (MouseGui::getPosition ());
	str.move(0, -20);
	window.draw (str);
}

inline void createNewNode (std::string& nameOfTheWindow)
{
	system (("notepad " + nameOfTheWindow + "/____new_event_script____.txt").c_str ());
	system (("python " + lexerPath + nameOfTheWindow + "/____new_event_script____.txt ____tokens____.txt").c_str ());
	// TODO: Parse tokens to lexical tree
}

void TreeGUI::update (sf::RenderWindow& window, std::string& nameOfTheWindow)
{
	if (sf::Mouse::isButtonPressed (sf::Mouse::Right)) { chooseAndGrowNode (); }
	else if (selected != nullptr) { someOneWasSelected = true; }
	else { requireTimeUp = false; }
	if (selected != nullptr && someOneWasSelected)
	{
		feedBackWhenNodeSelected (window);
		feedBackExitSelected (window);
	}
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::F)) { createNewNode (nameOfTheWindow); }
}

void TreeGUI::draw (sf::RenderWindow& window, std::string& nameOfTheWindow)
{
	this->update (window, nameOfTheWindow);
	for (auto& it : this->nodes) { it->draw (window); }
}

void TreeGUI::addNode () {nodes.push_back (std::shared_ptr<NodeGUI> (new NodeGUI ()));}
void TreeGUI::addNode (int x, int y) {nodes.push_back (std::shared_ptr<NodeGUI> (new NodeGUI (x, y)));}
void TreeGUI::addNode (const std::wstring& name) {nodes.push_back (std::shared_ptr<NodeGUI> (new NodeGUI (name)));}
void TreeGUI::addNode (const std::wstring& name, int x, int y) {nodes.push_back (std::shared_ptr<NodeGUI> (new NodeGUI (name, x, y)));}
