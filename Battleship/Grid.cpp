#include "Grid.h"
#include <iomanip> // For setw
#include <windows.h>

using namespace std;

Grid::Grid() {
    Initialize();
}

void Grid::Initialize() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            playerGrid[i][j] = '.';
}

void Grid::Display() {
    // Column headers
    cout << "   "; // Padding for top-left corner
    for (char col = 'A'; col <= 'J'; ++col)
        cout << setw(3) << col;
    cout << endl;

    // Rows with grid dots
    for (int row = 0; row < 10; ++row) {
        cout << setw(2) << row + 1 << " "; // Left-side row numbers aligned
        for (int col = 0; col < 10; ++col)
            cout << setw(3) << playerGrid[row][col];
        cout << endl;

    }
}

void Grid::DisplayWith(Grid& enemyGrid) {
    // Top headers
    cout << "  ";
    for (char col = 'A'; col <= 'J'; ++col)
        cout << setw(3) << col;

    cout << "      ";

    cout << "  ";
    for (char col = 'A'; col <= 'J'; ++col)
        cout << setw(3) << col;

    cout << endl;

    // Indicator Setup
    const string indicator[] = {
        " O   HIT",
        " X   MISS",
        "[S]  SHIP",
        " .   EMPTY"
    };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Grid Rows with Indicator (PASTE THIS PART)
    for (int i = 0; i < 10; ++i) {
        // Player grid row number (tight spacing)
        cout << setw(2) << i + 1;
        for (int j = 0; j < 10; ++j)
            cout << setw(3) << playerGrid[i][j];

        cout << "      ";

        // Enemy grid row number
        cout << setw(2) << i + 1;
        for (int j = 0; j < 10; ++j)
            cout << setw(3) << enemyGrid.playerGrid[i][j];

        cout << "      ";

        // Show indicator (between row 4 and 7)
        int indicatorStartRow = 3;
        if (i >= indicatorStartRow && i < indicatorStartRow + 4) {
            int index = i - indicatorStartRow;

            if (index == 0) SetConsoleTextAttribute(hConsole, 10); // Green
            else if (index == 1) SetConsoleTextAttribute(hConsole, 12); // Red
            else SetConsoleTextAttribute(hConsole, 7); // White

            cout << indicator[index];
            SetConsoleTextAttribute(hConsole, 7);
        }

        cout << endl;
    }
}
