#ifndef MenuUtils_H
#define MenuUtils_H

#include <iostream>
#include <windows.h>

using namespace std;

class MenuUtils {
public:
    static void ClearScreen();
    static void SetCursorPosition(int x, int y);
    static void PrintCentered(const string& text, int y); // Make sure this appears only once
    static void SetColor(int color); // New function for color handling
};

#endif // MenuUtils_H
