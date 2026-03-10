#include "gameMain.h"

#include <raylib.h>

#include <fstream>
#include <iostream>

bool initGame() { return true; }

bool updateGame() {
    DrawRectangleRec({50, 50, 100, 100}, {0, 255, 0, 127});
    DrawRectangleRec({75, 75, 100, 100}, {255, 0, 0, 127});

    return true;
}

void closeGame() {
    std::ofstream f(RESOURCES_PATH "f.txt");
    f << "\nCLOSED\n";
    f.close();
    std::cout << "Closing Game" << std::endl;
    return;
}
