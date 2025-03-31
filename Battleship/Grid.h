#pragma once
#include <iostream>
using namespace std;

class Grid {
    friend class Grid;

private:
    char mainGrid[10][10];

public:
    Grid();
    void Initialize();
    void Display();
    void DisplayWith(Grid& otherGrid);
    bool CanPlaceShip(int row, int col, int size, bool horizontal);
    void PlaceShip(int row, int col, int size, bool horizontal);
    void PlaceShipsRandomly();

};