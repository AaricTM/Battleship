#pragma once
#include "Grid.h"

class Game {
private:
    Grid playerGrid;
    Grid enemyGrid;
    bool isRunning;

public:
    Game();
    void Run();           // <- Replaces Start()
    void Render();        // Already exists
    void HandleInput();   // NEW – handles keys like ESC, etc.
    void PauseMenu();     // Already added earlier
};
