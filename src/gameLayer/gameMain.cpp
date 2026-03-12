#include "gameMain.h"

#include <imgui.h>
#include <raylib.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "assetManager.h"
#include "gameMap.h"
#include "helpers.h"

namespace GameLayer {

struct GameData {
    GameMap gameMap;
    Camera2D camera;
} gameData;

AssetManager assetManager;

bool initGame() {
    assetManager.loadAll();

    gameData.gameMap.create(30, 10);

    gameData.gameMap.getBlockUnsafe(0, 0).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(1, 1).type = Block::grass;
    gameData.gameMap.getBlockUnsafe(2, 2).type = Block::clay;
    gameData.gameMap.getBlockUnsafe(3, 3).type = Block::platform;
    gameData.gameMap.getBlockUnsafe(4, 4).type = Block::goldBlock;

    gameData.camera.target   = {0, 0};
    gameData.camera.rotation = 0.f;
    gameData.camera.zoom     = 100.f;

    return true;
}

bool updateGame() {
    float deltaTime = GetFrameTime();
    if ( deltaTime > 1.f / 5 ) {
        deltaTime = 1 / 5.f;
    }

    gameData.camera.offset = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};

    ClearBackground({75, 75, 150, 255});

#pragma region Camera Movement
    if ( IsKeyDown(KEY_UP) ) {
        gameData.camera.target.y -= 7.f * deltaTime;
    }
    if ( IsKeyDown(KEY_LEFT) ) {
        gameData.camera.target.x -= 7.f * deltaTime;
    }
    if ( IsKeyDown(KEY_DOWN) ) {
        gameData.camera.target.y += 7.f * deltaTime;
    }
    if ( IsKeyDown(KEY_RIGHT) ) {
        gameData.camera.target.x += 7.f * deltaTime;
    }
#pragma endregion

#pragma region Block Selector
    static char id[3]       = "";
    static uint16_t blockID = 0;
    ImGui::Begin("Debug Menu");
    ImGui::Text("Block ID: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(110.f);
    ImGui::InputTextWithHint("###ID", "0 - 53", id, IM_ARRAYSIZE(id));
    ImGui::SameLine();
    if ( ImGui::SmallButton("Clear") ) {
        id[0]   = '\0';
        blockID = 0;
    }
    if ( strlen(id) > 0 ) {
        blockID = static_cast<uint16_t>(std::stoi(id));
    }
    blockID = std::min(blockID, (uint16_t)(Block::BLOCKS_COUNT - 1));

#pragma endregion

#pragma region Mouse Logic
    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
    int blockX       = (int)floor(worldPos.x);
    int blockY       = (int)floor(worldPos.y);

    if ( !ImGui::IsWindowHovered() || !ImGui::IsWindowFocused() ) {
        if ( IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) {
            auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
            if ( b ) {
                b->type = blockID;
            }
        }

        if ( IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ) {
            auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
            if ( b ) {
                *b = {};
            }
        }
    }
#pragma endregion

    BeginMode2D(gameData.camera);

    for ( int y = 0; y < gameData.gameMap.h; y++ ) {
        for ( int x = 0; x < gameData.gameMap.w; x++ ) {
            auto &b = gameData.gameMap.getBlockUnsafe(x, y);

            if ( b.type != Block::air ) {
                DrawTexturePro(assetManager.textures,
                               getTextureAtlas(b.type, 0, 32, 32),
                               {(float)x, (float)y, 1, 1}, {}, 0.f, WHITE);
            }
        }
    }

    DrawTexturePro(assetManager.frame,
                   {0, 0, (float)assetManager.frame.width,
                    (float)assetManager.frame.height},
                   {(float)blockX, (float)blockY, 1, 1}, {}, 0.f, WHITE);

    EndMode2D();

    ImGui::End();
    return true;
}

void closeGame() {
    std::ofstream f(RESOURCES_PATH "f.txt");
    f << "\nCLOSED\n";
    f.close();
}
};  // namespace GameLayer
