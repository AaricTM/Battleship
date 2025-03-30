#include "Menu.h"
#include "MenuUtils.h"
#include <iostream>
#include <conio.h>
#include <fstream> // Include this at the top for file reading
#include "Game.h"

using namespace std;

Menu::Menu() {
    menu_options = { "Play", "Options", "Quit" };
    choice = 0;
    screen_width = 80; // Default console width
}

void SetConsoleSize() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Get current console width & height
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // Resize console dynamically
        SMALL_RECT rect = { 0, 0, consoleWidth - 1, consoleHeight - 1 };
        SetConsoleWindowInfo(hConsole, TRUE, &rect);
    }
}

void Menu::DisplayMenu() {
    SetConsoleSize(); // Dynamically adjust console size
    MenuUtils::ClearScreen();

    // Get console width dynamically
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int screen_width = 80; // Default width
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        screen_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Open the file and read the ASCII text
    ifstream file("battleship.txt");
    int y = 2; // Starting Y position
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int text_pos = max(0, (screen_width - line.length()) / 2);
            MenuUtils::SetCursorPosition(text_pos, y++);
            cout << line;
        }
        file.close();
    }
    else {
        MenuUtils::PrintCentered("Welcome to Battleship!", y++);
    }

    // **Print subtext below the ASCII title in yellow**
    y += 1; // Add spacing below the title
    MenuUtils::SetColor(14); // Yellow text color
    MenuUtils::PrintCentered("(Move around using arrow keys or WASD, to Confirm press Enter Key, To go back press ESC key)", y++);
    MenuUtils::SetColor(7);  // Reset text color to default (white)

    // Print menu options
    for (size_t i = 0; i < menu_options.size(); i++) {
        int option_pos = max(0, (screen_width - menu_options[i].size()) / 2);
        MenuUtils::SetCursorPosition(option_pos, y + i + 1);

        if (i == choice) {
            cout << "--> " << menu_options[i];
        }
        else {
            cout << "    " << menu_options[i];
        }
    }
}

void Menu::DifficultyMenu() {
    menu_options = { "Easy", "Medium", "Hard", "Back" };
    choice = 0; // Reset selection to the first option

    char key;
    while (true) {
        MenuUtils::ClearScreen();

        string title = "Select Difficulty";
        int title_pos = (screen_width - title.size()) / 2;
        MenuUtils::SetCursorPosition(title_pos, 3);
        cout << title << "\n\n";

        // Print difficulty options with color
        for (size_t i = 0; i < menu_options.size(); i++) {
            int option_pos = max(0, (screen_width - menu_options[i].size()) / 2);
            MenuUtils::SetCursorPosition(option_pos, 5 + i);

            // Set color based on difficulty option
            if (i == 0) MenuUtils::SetColor(10); // Green for Easy
            else if (i == 1) MenuUtils::SetColor(6); // Orange (Dark Yellow) for Medium
            else if (i == 2) MenuUtils::SetColor(12); // Red for Hard
            else MenuUtils::SetColor(7); // White for Back

            // Highlight selected option
            if (i == choice) {
                cout << "--> " << menu_options[i];
            }
            else {
                cout << "    " << menu_options[i];
            }
        }

        MenuUtils::SetColor(7); // Reset to default color

        key = _getch();

        // Handle navigation
        if (key == -32 || key == 224) { // Detect arrow keys
            key = _getch();
            if (key == 72) // Up Arrow
                choice = (choice - 1 + menu_options.size()) % menu_options.size();
            else if (key == 80) // Down Arrow
                choice = (choice + 1) % menu_options.size();
        }
        else if (key == 'w' || key == 'W') // W Key (up)
            choice = (choice - 1 + menu_options.size()) % menu_options.size();
        else if (key == 's' || key == 'S') // S Key (down)
            choice = (choice + 1) % menu_options.size();
        else if (key == 13) { // Enter key
            if (choice == 3) { // Back option
                menu_options = { "Play", "Options", "Quit" };
                choice = 0; // Reset selection
                return; // Return to Main Menu
            }

            // Display "Starting Game..." before launching
            MenuUtils::ClearScreen();
            MenuUtils::PrintCentered("Starting Game...", 10);
            Sleep(2000);

            Game game;
            game.Run();

            menu_options = { "Play", "Options", "Quit" };
            choice = 0; // Reset selection

            return;
        }
        else if (key == 27) { // ESC key
            menu_options = { "Play", "Options", "Quit" };
            choice = 0; // Reset selection
            return;
        }
    }
}

void Menu::Run() {
    char key;
    while (true) {
        DisplayMenu();
        key = _getch(); // Get user input

        if (key == -32 || key == 224) { // Detect special keys (Arrow keys)
            key = _getch();
            if (key == 72) // Up Arrow
                choice = (choice - 1 + menu_options.size()) % menu_options.size();
            else if (key == 80) // Down Arrow
                choice = (choice + 1) % menu_options.size();
        }
        else if (key == 'w' || key == 'W') // W Key (up)
            choice = (choice - 1 + menu_options.size()) % menu_options.size();
        else if (key == 's' || key == 'S') // S Key (down)
            choice = (choice + 1) % menu_options.size();
        else if (key == 13) { // Enter key (⏎)
            MenuUtils::ClearScreen();
            switch (choice) {
            case 0: // Play
                DifficultyMenu(); // Show Difficulty Menu first
                break;
            case 1: // Options
                OptionMenu();
                break;
            case 2: // Quit
                return; // Exit menu loop
            }
        }
    }
}

void Menu::Start() {
    cout << "Game Starting...\n";
    system("pause");
}

void Menu::OptionMenu() {
    menu_options = { "Introduction", "Controls", "Back" }; // Removed "Difficulty"
    choice = 0; // Reset selection to the first option when entering

    char key;
    while (true) {
        MenuUtils::ClearScreen();

        string title = "Options Menu";
        int title_pos = (screen_width - title.size()) / 2;
        MenuUtils::SetCursorPosition(title_pos, 3);
        cout << title << "\n\n";

        for (size_t i = 0; i < menu_options.size(); i++) {
            int option_pos = max(0, (screen_width - menu_options[i].size()) / 2);
            MenuUtils::SetCursorPosition(option_pos, 5 + i);

            if (i == choice) {
                cout << "--> " << menu_options[i];
            }
            else {
                cout << "    " << menu_options[i];
            }
        }

        key = _getch();

        if (key == -32 || key == 224) {
            key = _getch();
            if (key == 72) // Up Arrow
                choice = (choice - 1 + menu_options.size()) % menu_options.size();
            else if (key == 80) // Down Arrow
                choice = (choice + 1) % menu_options.size();
        }
        else if (key == 'w' || key == 'W') // W Key (up)
            choice = (choice - 1 + menu_options.size()) % menu_options.size();
        else if (key == 's' || key == 'S') // S Key (down)
            choice = (choice + 1) % menu_options.size();
        else if (key == 13) { // Enter key
            MenuUtils::ClearScreen();
            switch (choice) {
            case 0:
                ShowIntroduction();
                break;
            case 1:
                ShowControls();
                break;
            case 2:
                menu_options = { "Play", "Options", "Quit" };
                choice = 0;
                return;
            }
        }
        else if (key == 27) { // ESC key (27)
            menu_options = { "Play", "Options", "Quit" };
            choice = 0;
            return;
        }
    }
}

void Menu::ShowIntroduction() {
    MenuUtils::ClearScreen();

    MenuUtils::PrintCentered("Welcome to Battleship!", 3);
    MenuUtils::PrintCentered("How to Play:", 5);
    MenuUtils::PrintCentered("- Use the arrow keys or WASD to navigate.", 7);
    MenuUtils::PrintCentered("- Select 'Play' to start the game.", 8);
    MenuUtils::PrintCentered("- Choose 'Options' to adjust settings.", 9);
    MenuUtils::PrintCentered("- Sink all enemy ships to win!", 10);

    MenuUtils::PrintCentered("Press any key to go back...", 12);
    _getch(); // Wait for user input before returning
}

void Menu::ShowControls() {
    MenuUtils::ClearScreen();

    MenuUtils::PrintCentered("Game Controls", 3);
    MenuUtils::PrintCentered("Movement:", 5);
    MenuUtils::PrintCentered("- W / Up Arrow: Move Up", 7);
    MenuUtils::PrintCentered("- S / Down Arrow: Move Down", 8);
    MenuUtils::PrintCentered("- A / Left Arrow: Move Left", 9);
    MenuUtils::PrintCentered("- D / Right Arrow: Move Right", 10);

    MenuUtils::PrintCentered("Other Actions:", 12);
    MenuUtils::PrintCentered("- Enter: Confirm / Select", 14);
    MenuUtils::PrintCentered("- ESC: Go Back", 15);

    MenuUtils::PrintCentered("Press any key to go back...", 17);
    _getch(); // Wait for user input before returning
}
