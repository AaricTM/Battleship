#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class Menu {
private:
    vector<string> menu_options;
    int choice;
    int screen_width;
public:
    Menu();
    void DisplayMenu();
    void Run();
    void Start();
    void StartGame();
    bool PauseMenu();
    void RenderGameScreen();
    void OptionMenu();
    void Options();
    void DifficultyMenu();
    void DiffMenu();
    void ShowIntroduction();
    void ShowControls();

};

#endif // MENU_H
