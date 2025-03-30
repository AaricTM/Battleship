#pragma once
#include <iostream>
using namespace std;

class Grid {
    friend class Grid;

private:
    char playerGrid[10][10];

public:
    Grid();
    void Initialize();
    void Display();
    void DisplayWith(Grid& otherGrid);
};