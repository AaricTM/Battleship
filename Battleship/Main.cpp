#include "Menu.h"
#include "Game.h"
#include <windows.h>
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(0));
    Menu menu;
    menu.Run();
    return 0;
}
