#include "win_file_sys.h"

const std::string lexerPath = "../lexer.py";


void mkdir (const char* path) {system (("mkdir " + std::string (path)).c_str ());}

void rm (const char* path) {system (("del " + std::string (path)).c_str ());}

void lsDirs (std::vector<std::string>& dirs, const char* path = nullptr)
{
	std::string line;
	if (path != nullptr) {system (("chcp 1251 | dir > " + std::string (path) + "/______dirFile____.txt | chcp 866 | cls").c_str ());}
	else {system ("chcp 1251 | dir > ______dirFile____.txt | chcp 866 | cls");}
	std::ifstream input (((path != nullptr) ? std::string(path)+"/" : "")+"______dirFile____.txt");
	while (!input.eof ())
	{
		std::getline (input, line);
		if(line.find ("<DIR>") != std::string::npos) {dirs.push_back (line.substr (36));}
	}
	input.close ();
	system ("del ______dirFile____.txt");
	dirs.erase (std::begin (dirs), std::begin (dirs) + 2);
}

void lsFiles (const char* path, std::vector<std::string>& files)
{
	std::string line;
	if (path != nullptr) {system (("chcp 1251 | dir > " + std::string (path) + "/______dirFile____.txt | chcp 866 | cls").c_str ());}
	else {system ("chcp 1251 | dir > ______dirFile____.txt | chcp 866 | cls");}
	std::ifstream input (((path != nullptr) ? std::string(path)+"/" : "")+"______dirFile____.txt");
	while (!input.eof ())
	{
		std::getline (input, line);
		if(line.find ("<DIR>") == std::string::npos && line.find ("\\") == std::string::npos && line.find (":") != std::string::npos) {files.push_back (line.substr (36));}
	}
	input.close ();
	system ("del ______dirFile____.txt");
}

void ls (const char* path, std::vector<std::string>& all)
{
	std::string line;
	if (path != nullptr) {system (("chcp 1251 | dir > " + std::string (path) + "/______dirFile____.txt | chcp 866 | cls").c_str ());}
	else {system ("chcp 1251 | dir > ______dirFile____.txt | chcp 866 | cls");}
	std::ifstream input (((path != nullptr) ? std::string(path)+"/" : "")+"______dirFile____.txt");
	while (!input.eof ())
	{
		std::getline (input, line);
		if (line.find ("\\") == std::string::npos && line.find (":") != std::string::npos) {all.push_back (line.substr (36));}
	}
	input.close ();
	system ("del ______dirFile____.txt");
	all.erase (std::begin (all), std::begin (all) + 2);
}

void touch (const char* path)
{
	std::ofstream input (path);
	input.close ();
}

void lexer (const char* from, std::vector<std::string>& to)
{
	system (("python " + lexerPath + " " + std::string (from) + " ______tokens____.txt").c_str ());
	bool isString = false;
	std::ifstream input ("______tokens____.txt");
	if (input.is_open ())
	{
		std::string buff;
		while (!input.eof ())
		{
			std::getline (input, buff);
			if (buff != "\"")
			{
				if (isString) {to.back() += buff + "\n";} else {to.push_back (buff);}
			}
			else
			{
				isString = !isString;
				if (isString) {to.push_back (buff);}
			}
		}
		input.close ();
	}
}
