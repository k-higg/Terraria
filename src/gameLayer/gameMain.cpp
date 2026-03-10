#include "gameMain.h"

#include <raylib.h>

#include <fstream>

namespace GameLayer {

struct GameData {
    float positionX = 100;
    float positionY = 100;
} gameData;

bool initGame() { return true; }

bool updateGame() {
    const float deltaTime = GetFrameTime();

    DrawRectangleRec({gameData.positionX, gameData.positionY, 100, 100},
                     {0, 255, 0, 127});

    if ( IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ) {
        gameData.positionY -= 500 * deltaTime;
    }
    if ( IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ) {
        gameData.positionX -= 500 * deltaTime;
    }
    if ( IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ) {
        gameData.positionY += 500 * deltaTime;
    }
    if ( IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ) {
        gameData.positionX += 500 * deltaTime;
    }

    return true;
}

void closeGame() {
    std::ofstream f(RESOURCES_PATH "f.txt");
    f << "\nCLOSED\n";
    f.close();
}

};  // namespace GameLayer
