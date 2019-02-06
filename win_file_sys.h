#ifndef WIN_FILE_SYS_H
#define WIN_FILE_SYS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void mkdir (const char* path);
void rm (const char* path);
void lsDirs (const char* path, std::vector<std::string>& dirs);
void lsFiles (const char* path, std::vector<std::string>& files);
void ls (const char* path, std::vector<std::string>& all);
void touch (const char* path);
void addToFile (std::ifstream& input, const char* data);

#endif // WIN_FILE_SYS_H
