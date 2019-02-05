#include "aliasesForMainWorkcycle.h"


//---------------------------------------------------------------------------//

inline void enteringDataAndLoadingEnteredData (
		std::string& nameOfTheWindow,
		std::string& description,
		char* buff,
		unsigned size)
{
	system ("echo new_act > ____nameOfTheAct____.txt");
	system ("notepad ____nameOfTheAct____.txt");
	std::ifstream input ("____nameOfTheAct____.txt");
	input.getline (buff, size);
	nameOfTheWindow = buff;
	while (!input.eof ())
	{
		input.getline (buff, size);
		description += buff;
		if (!input.eof ()) description += '\n';
	}
	input.close ();
	system ("del ____nameOfTheAct____.txt");
}

inline void creationOfThePathWithNewProject (std::string& nameOfTheWindow, std::string& description)
{
	system (("mkdir \"" + nameOfTheWindow).c_str ());
	std::ofstream output (("./" + nameOfTheWindow + "/act.txt").c_str (), std::ios::out | std::ios::app);
	output << '#' << nameOfTheWindow << "\n\"\n" << description << "\n\"\n";
	output.close ();
}

inline void showSimpleMenu (char& ch, int& i, std::vector<std::string>* p)
{
	do
	{
		system ("cls");
		if (ch == 'w') --i; else if (ch == 's') ++i;
		if (i >= static_cast<int> (p->size ())) i = 0;
		else if (i < 0) i = static_cast<int> (p->size ()) - 1;
		for (unsigned j = 0; j < p->size (); ++j)
		{
			std::cout << (static_cast<int> (j) == i ? "->" : "  ") << (*p)[j] << '\n';
		}
		ch = static_cast<char> (getch ());
	}
	while('d' != ch);
}

inline void getLeafsOfCurrentPath (std::vector<std::string>& allActs)
{
	std::string line;
	system ("chcp 1251 | dir > ____dirFile____.txt | chcp 866 | cls");
	std::ifstream input ("____dirFile____.txt");
	while (!input.eof ())
	{
		std::getline (input, line);
		if(line.find("<DIR>")!=std::string::npos)
		{
			allActs.push_back(line.substr (36));
		}
	}
	input.close ();
	system ("del ____dirFile____.txt");
	allActs.erase (std::begin (allActs), std::begin (allActs) + 2);
}

inline void loadAct (std::string& nameOfAct)
{
	system (("cd "+nameOfAct).c_str ());
	system ("cd ..");
}

int enterMenu (std::string& nameOfTheWindow, std::string& description)
{
	char ch = ' ';
	int i = 0;
	std::vector<std::string> menu = {
		"New act",
		"Load recent act",
		" [ exit ]"
	};
	while (true)
	{
		showSimpleMenu (ch, i, &menu);
		if (i == 0)
		{
			system ("cls");
			char buff[200];
			enteringDataAndLoadingEnteredData (nameOfTheWindow, description,buff,200);
			std::vector<std::string> vec;
			getLeafsOfCurrentPath (vec);
			bool tr = true;
			for (auto& it : vec) if (it == nameOfTheWindow) {tr = false; break;}
			if (tr) creationOfThePathWithNewProject (nameOfTheWindow, description);
			break;
		}

		if (i == 1)
		{
			std::vector<std::string> allActs;
			getLeafsOfCurrentPath (allActs);
			allActs.push_back (" [ back ]");
			int j = 0;
			showSimpleMenu (ch, j, &allActs);
			if (j < static_cast<int>(allActs.size ()) - 1)
			{
				loadAct (allActs[static_cast<unsigned>(j)]);
				break;
			}
		}

		if (i == 2) { return 0; }
	}
	return 1;
}

//---------------------------------------------------------------------------//


void controlView (sf::View& view, sf::RenderWindow& window)
{
	using namespace tot;
	const float zoomVel = 0.01f * getDTime ();
	const float viewVel = 5.f * view.getSize ().x / window.getSize ().x;
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::E)) { view.zoom(1.f - zoomVel); }
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Q)) { view.zoom(1.f + zoomVel); }
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::S)) { view.move(0, viewVel * getDTime ()); }
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::W)) { view.move(0, -viewVel * getDTime ()); }
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::D)) { view.move(viewVel * getDTime (), 0); }
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::A)) { view.move(-viewVel * getDTime (), 0); }
}

void init (sf::RenderWindow& window, sf::View& view, TreeGUI& tree)
{
	MouseGui::window = &window;
	view.setCenter (0, 0);
	view.setSize (2*400, 2*300);
	NodeGUI::font.loadFromFile ("FiraCode-Regular.otf");

	tree.addNode (L"Начало", -180, -120);
	tree.addNode (L"Конец", 80, 50);
}

void workOnAllEvents (sf::RenderWindow& window)
{
	sf::Event event;
	tot::updateDTime ();
	while (window.pollEvent (event))
	{
		if (event.type == sf::Event::Closed //|| sf::Keyboard::isKeyPressed (sf::Keyboard::Return))
			|| sf::Keyboard::isKeyPressed (sf::Keyboard::Escape))
		{
			window.close ();
		}
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			for (auto& it : MouseGui::wheelFuncs)
			{
				it (static_cast<int> (event.mouseWheelScroll.delta));
			}
		}
	}
}
