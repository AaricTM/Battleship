#include "Menu.h"
#include "Utilities.h"
#include <iostream>
#include <conio.h>
#include <fstream> // Include this at the top for file reading

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
    SetConsoleSize(); // Dynamically set console size

    Utilities::ClearScreen();

    // Get console width dynamically
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int screen_width = 80; // Default width
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        screen_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Open the file and read the ASCII text
    ifstream file("Battleship.txt");
    if (file.is_open()) {
        string line;
        int y = 2; // Start printing at a specific line
        while (getline(file, line)) {
            int text_pos = max(0, (screen_width - line.length()) / 2); // Ensure non-negative position
            Utilities::SetCursorPosition(text_pos, y++);
            cout << line;
        }
        file.close();
    }
    else {
        // Fallback if the file can't be opened
        Utilities::PrintCentered("Welcome to Battleship!", 2);
    }

    // Print menu options
    for (size_t i = 0; i < menu_options.size(); i++) {
        int option_pos = max(0, (screen_width - menu_options[i].size()) / 2);
        Utilities::SetCursorPosition(option_pos, 10 + i);

        if (i == choice) {
            cout << "--> " << menu_options[i]; // Highlight selection
        }
        else {
            cout << "    " << menu_options[i];
        }
    }
}

void Menu::DiffMenu() {
    menu_options = { "Easy", "Medium", "Hard", "Back" };
    choice = 0;
    screen_width = 80; // Default console width
}

void Menu::DifficultyMenu() {
    menu_options = { "Easy", "Medium", "Hard", "Back" };
    choice = 0; // Reset selection to the first option when entering

    char key;
    while (true) {
        Utilities::ClearScreen();

        string title = "Select Difficulty";
        int title_pos = (screen_width - title.size()) / 2;
        Utilities::SetCursorPosition(title_pos, 3);
        cout << title << "\n\n";

        // Print difficulty options
        for (size_t i = 0; i < menu_options.size(); i++) {
            int option_pos = max(0, (screen_width - menu_options[i].size()) / 2);
            Utilities::SetCursorPosition(option_pos, 5 + i);

            if (i == choice) {
                cout << "--> " << menu_options[i];
            }
            else {
                cout << "    " << menu_options[i];
            }
        }

        // Capture user input
        key = _getch();

        // Handle navigation
        if (key == 224) {
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
            if (choice == 3) {
                menu_options = { "Difficulty", "Introduction", "Controls", "Back" };
                choice = 0; // Reset selection when going back to Options Menu
                return;
            }
        }
        else if (key == 27) { // ESC key
            menu_options = { "Difficulty", "Introduction", "Controls", "Back" };
            choice = 0; // Reset selection when going back to Options Menu
            return;
        }
    }
}

void Menu::Run() {
    char key;
    while (true) {
        DisplayMenu();
        key = _getch(); // Get user input

        if (key == 224) { // Arrow keys return two codes, first one is always 224
            key = _getch(); // Get the actual key code
            if (key == 72) // Up Arrow
                choice = (choice - 1 + menu_options.size()) % menu_options.size();
            else if (key == 80) // Down Arrow
                choice = (choice + 1) % menu_options.size();
        }
        else if (key == 'w' || key == 'W') // W Key (up)
            choice = (choice - 1 + menu_options.size()) % menu_options.size();
        else if (key == 's' || key == 'S') // S Key (down)
            choice = (choice + 1) % menu_options.size();
        else if (key == 13) { // Enter key (Selection)
            Utilities::ClearScreen();
            switch (choice) {
            case 0:
                Start();
                break;
            case 1:
                Options();
                break;
            case 2:
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
    menu_options = { "Difficulty", "Introduction", "Back" };
    choice = 0;
    screen_width = 80; // Default console width
}

void Menu::Options() {
    menu_options = { "Difficulty", "Introduction", "Controls", "Back" };
    choice = 0; // Reset selection to the first option when entering

    char key;
    while (true) {
        Utilities::ClearScreen();

        string title = "Options Menu";
        int title_pos = (screen_width - title.size()) / 2;
        Utilities::SetCursorPosition(title_pos, 3);
        cout << title << "\n\n";

        // Print menu options
        for (size_t i = 0; i < menu_options.size(); i++) {
            int option_pos = max(0, (screen_width - menu_options[i].size()) / 2);
            Utilities::SetCursorPosition(option_pos, 5 + i);

            if (i == choice) {
                cout << "--> " << menu_options[i]; // Highlight selection
            }
            else {
                cout << "    " << menu_options[i];
            }
        }

        // Capture user input
        key = _getch();

        // Handle navigation
        if (key == 224) {
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
            Utilities::ClearScreen();
            switch (choice) {
            case 0:
                DifficultyMenu();
                break;
            case 1:
                ShowIntroduction();
                break;
            case 2:
                ShowControls();
                break;
            case 3:
                menu_options = { "Play", "Options", "Quit" };
                choice = 0; // Reset selection when going back to Main Menu
                return;
            }
        }
        else if (key == 27) { // ESC key
            menu_options = { "Play", "Options", "Quit" };
            choice = 0; // Reset selection when going back to Main Menu
            return;
        }
    }
}

void Menu::ShowIntroduction() {
    Utilities::ClearScreen();

    Utilities::PrintCentered("Welcome to Battleship!", 3);
    Utilities::PrintCentered("How to Play:", 5);
    Utilities::PrintCentered("- Use the arrow keys or WASD to navigate.", 7);
    Utilities::PrintCentered("- Select 'Play' to start the game.", 8);
    Utilities::PrintCentered("- Choose 'Options' to adjust settings.", 9);
    Utilities::PrintCentered("- Sink all enemy ships to win!", 10);

    Utilities::PrintCentered("Press any key to go back...", 12);
    _getch(); // Wait for user input before returning
}

void Menu::ShowControls() {
    Utilities::ClearScreen();

    Utilities::PrintCentered("Game Controls", 3);
    Utilities::PrintCentered("Movement:", 5);
    Utilities::PrintCentered("- W / Up Arrow: Move Up", 7);
    Utilities::PrintCentered("- S / Down Arrow: Move Down", 8);
    Utilities::PrintCentered("- A / Left Arrow: Move Left", 9);
    Utilities::PrintCentered("- D / Right Arrow: Move Right", 10);
    
    Utilities::PrintCentered("Other Actions:", 12);
    Utilities::PrintCentered("- Enter: Confirm / Select", 14);
    Utilities::PrintCentered("- ESC: Go Back", 15);

    Utilities::PrintCentered("Press any key to go back...", 17);
    _getch(); // Wait for user input before returning
}
