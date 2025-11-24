#ifndef UTILITY_H
#define UTILITY_H

#include <string>
using namespace std;  

string readLine();
string toLower(const string& str);
int compareIgnoreCase(const string& a, const string& b);
string getTimestamp();

// === NEW GUI FUNCTIONS ===
void clearScreen();
void pause();
void printHeader(const string& title);
void setConsoleColor(int colorCode);

#endif