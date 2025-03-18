#include "Utilities.h"
#include <windows.h>
#include <iostream>

using namespace std; // This removes the need for std::

void Utilities::ClearScreen() {
    system("CLS");
}

void Utilities::SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Utilities::PrintCentered(const string& text, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int screen_width = 80; // Default width
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        screen_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    int text_pos = max(0, (screen_width - text.length()) / 2); // Prevent negative position
    SetCursorPosition(text_pos, y);
    cout << text;
}
