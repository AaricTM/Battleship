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
    void OptionMenu();
    void DifficultyMenu(); 
    void ShowIntroduction();
    void ShowControls();

};

#endif // MENU_H
