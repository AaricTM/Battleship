#include "Game.h"
#include <iostream>
#include <conio.h> // For _getch()
#include <windows.h>

using namespace std;

Game::Game() {
    isRunning = true;
}

void Game::Run() {
    isRunning = true;
    playerGrid.Initialize();

    while (isRunning) {
        Render();        // Draw grid & labels
        HandleInput();   // Get user input (like ESC)
        // Update();     // Future: turn progression, fire logic, etc.
    }
}

void Game::Render() {
    system("cls");

    cout << "\nPlayer:                               Enemy:\n" << endl;
    playerGrid.DisplayWith(enemyGrid);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14); // Yellow
    cout << "\n\n[R to rotate]  [Enter to confirm]  [X to reset]  [ESC to pause the game]" << endl;
    SetConsoleTextAttribute(hConsole, 7); // Reset
}

void Game::PauseMenu() {
    int selection = 0;
    const string OptionMenu[2] = { "Continue Playing", "Quit" };

    while (true) {
        system("cls");
        cout << "Would you like to quit?\n\n";

        for (int i = 0; i < 2; ++i) {
            if (i == selection)
                cout << "> ";
            else
                cout << "  ";

            cout << OptionMenu[i] << endl;
        }

        int key = _getch();
        if (key == 72 || key == 'w' || key == 'W') { // Up
            if (selection > 0) selection--;
        }
        else if (key == 80 || key == 's' || key == 'S') { // Down
            if (selection < 1) selection++;
        }
        else if (key == 13) { // Enter
            if (selection == 0) {
                Render(); // Resume game
                return;
            }
            else {
                isRunning = false; // Quit game loop
                return;
            }
        }
    }
}

void Game::HandleInput() {
    int key = _getch();

    if (key == 27) { // ESC
        PauseMenu();
    }

    // Future: Add Enter to shoot, arrow keys to move selector, etc.
}
 