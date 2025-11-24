#include <windows.h> 
#include "Utility.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib> 
string readLine() 
{
    string input;
    getline(cin, input);
    return input;
}
 
string toLower(const string& str) 
{
    string result = str;
    for (char& c : result) c = tolower(c);
    return result;
}
 
int compareIgnoreCase(const string& a, const string& b) 
{
    string lowerA = toLower(a);
    string lowerB = toLower(b);
    if (lowerA < lowerB) return -1;
    if (lowerA > lowerB) return 1;
    return 0;
}

string getTimestamp() 
{
    time_t t = time(nullptr);
    tm* tmStruct = localtime(&t);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d",
             tmStruct->tm_year + 1900, tmStruct->tm_mon + 1, tmStruct->tm_mday,
             tmStruct->tm_hour, tmStruct->tm_min, tmStruct->tm_sec);
    return string(buffer);
}

// === GUI IMPLEMENTATIONS ===

void clearScreen() 
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() 
{
    cout << "\nPress ENTER to continue...";
    cin.ignore(10000, '\n');
    cin.get(); 
}

void printHeader(const string& title) 
{
    clearScreen();
    setConsoleColor(11); // Cyan
    cout << "==========================================\n";
    cout << "   " << title << "\n";
    cout << "==========================================\n";
    setConsoleColor(7); // White
    cout << endl;
}

void setConsoleColor(int colorCode) 
{
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, colorCode);
    #endif
}