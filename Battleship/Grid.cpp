#include "Grid.h"
#include <iomanip> // For setw
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

Grid::Grid() {
    Initialize();
}

void Grid::Initialize() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            mainGrid[i][j] = '.';
}

void Grid::Display() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Declare once here

    // Column headers
    cout << "   ";
    for (char col = 'A'; col <= 'J'; ++col)
        cout << setw(3) << col;
    cout << endl;

    // Grid rows
    for (int row = 0; row < 10; ++row) {
        cout << setw(2) << row + 1 << " ";

        for (int col = 0; col < 10; ++col) {
            char cell = mainGrid[row][col];

            // Set color based on cell content
            if (cell == '.')
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            else
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // white

            cout << setw(3) << cell;

            // Reset color after each cell
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }

        cout << endl;
    }
}

void Grid::DisplayWith(Grid& enemyGrid) {
    // 1. Top Headers 
    cout << "  ";
    for (char col = 'A'; col <= 'J'; ++col)
        cout << setw(3) << col;

    cout << "    ";

    cout << "  ";
    for (char col = 'A'; col <= 'J'; ++col)
        cout << setw(3) << col;

    cout << endl;

    // 2. Indicator Setup
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const string indicator[] = {
        "O", " - HIT",
        "X", " - MISS",
        "S", " - SHIP",
        ".", " - EMPTY"
    };

    // 3. Display player & enemy grid rows, and attach indicator
    for (int row = 0; row < 10; ++row) {
        // Row number (player)
        cout << setw(2) << row + 1;

        // Player grid row
        for (int col = 0; col < 10; ++col)
            cout << setw(3) << mainGrid[row][col];

        cout << "    "; // Space between grids

        // Row number (enemy)
        cout << setw(2) << row + 1;

        // Enemy grid row
        for (int col = 0; col < 10; ++col)
            cout << setw(3) << enemyGrid.mainGrid[row][col];

        // === Add indicator to the right of rows 0–3 only ===
        int indicatorStartRow = 3; // Change this to shift it up or down

        if (row >= indicatorStartRow && row < indicatorStartRow + 4) {
            int i = row - indicatorStartRow; // index from 0 to 3

            cout << "    ";

            if (indicator[i * 2] == "O")
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            else if (indicator[i * 2] == "X")
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            else if (indicator[i * 2] == "S")
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            else if (indicator[i * 2] == ".")
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

            cout << indicator[i * 2];

            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << indicator[i * 2 + 1];
        }

        cout << endl;
    }
}

bool Grid::CanPlaceShip(int row, int col, int size, bool horizontal) {
    // Step 1: Check if ship fits inside the grid
    if (horizontal) {
        if (col < 0 || col + size > 10) return false;
    }
    else {
        if (row < 0 || row + size > 10) return false;
    }

    // Step 2: Check surrounding 1-cell buffer for other ships
    int dr = horizontal ? 0 : 1;
    int dc = horizontal ? 1 : 0;

    for (int i = -1; i <= size; ++i) {
        for (int rOffset = -1; rOffset <= 1; ++rOffset) {
            for (int cOffset = -1; cOffset <= 1; ++cOffset) {
                int r = row + dr * i + rOffset;
                int c = col + dc * i + cOffset;

                if (r >= 0 && r < 10 && c >= 0 && c < 10) {
                    if (mainGrid[r][c] == 'S') {
                        return false; // adjacent or overlapping
                    }
                }
            }
        }
    }

    return true;
}


void Grid::PlaceShip(int row, int col, int size, bool horizontal) {
    if (horizontal) {
        for (int i = 0; i < size; ++i)
            mainGrid[row][col + i] = 'S';
    }
    else {
        for (int i = 0; i < size; ++i)
            mainGrid[row + i][col] = 'S';
    }
}

void Grid::PlaceShipsRandomly() {
    const vector<int> shipSizes = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    for (int size : shipSizes) {
        bool placed = false;

        while (!placed) {
            int row = rand() % 10;
            int col = rand() % 10;
            bool horizontal = rand() % 2;

            if (CanPlaceShip(row, col, size, horizontal)) {
                PlaceShip(row, col, size, horizontal);
                placed = true;
            }
        }
    }
}
