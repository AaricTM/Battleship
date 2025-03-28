#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <windows.h>

using namespace std;

class Utilities {
public:
    static void ClearScreen();
    static void SetCursorPosition(int x, int y);
    static void PrintCentered(const string& text, int y); // Make sure this appears only once
    static void SetColor(int color); // New function for color handling
};

#endif // UTILITIES_H
