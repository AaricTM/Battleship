#include "Game.h"
#include <iostream>
#include <conio.h> // For _getch()
#include <windows.h>

using namespace std;

Game::Game() {
    isRunning = true;
}

void Game::Run() {
    playerGrid.Initialize(); // Clear board
    enemyGrid.Initialize();

    playerGrid.PlaceShipsRandomly(); // Place player's ships
    enemyGrid.PlaceShipsRandomly();  // Place enemy's ships

    // Temporary: Display for debugging
    playerGrid.Display();
    enemyGrid.Display();

    isRunning = true;

    while (isRunning) {
        Render();        // Show game state
        HandleInput();   // Handle keypresses like ESC, etc.
        // Update();     // In future: turn logic, firing, etc.
    }
}

void Game::Render() {
    system("cls");

    cout << "\nPlayer:                            Enemy:\n" << endl;
    playerGrid.DisplayWith(enemyGrid);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14); // Yellow
    cout << "\n\n[R to rotate]  [Enter to confirm]  [ESC to pause the game]" << endl;
    SetConsoleTextAttribute(hConsole, 7); // Reset
}

string center_text(const string& text, int width = 80) {
    int padding = (width - text.length()) / 2;
    if (padding < 0) padding = 0;
    return string(padding, ' ') + text;
}

void Game::PauseMenu() {
    int selection = 0;
    const string OptionMenu[3] = { "Continue Playing", "Restart", "Quit" };

    while (true) {
        system("cls");
        const int screenHeight = 25;
        const int menuStartLine = (screenHeight / 2) - (3 / 2);

        for (int i = 0; i < menuStartLine; ++i)
            cout << endl;

        cout << center_text("Pause Menu:") << "\n\n";

        for (int i = 0; i < 3; ++i) {
            string line = (i == selection ? "> " : "  ") + OptionMenu[i];
            cout << center_text(line) << endl;
        }

        int key = _getch();
        if (key == 72 || key == 'w' || key == 'W') selection--;
        else if (key == 80 || key == 's' || key == 'S') selection++;

        if (selection < 0) selection = 0;
        if (selection > 2) selection = 2;

        else if (key == 13) {
            if (selection == 0) { Render(); return; }
            else if (selection == 1) { Run(); return; }
            else { isRunning = false; return; }
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
 