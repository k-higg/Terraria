#include "gameMain.h"

#include <imgui.h>
#include <raylib.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <string>

#include "assetManager.h"
#include "gameMap.h"
#include "helpers.h"
#include "raymath.h"

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
    Block::Type blockType   = Block::Type::air;
    startDebugMenu(id, sizeof(id), &blockID);
    blockType = static_cast<Block::Type>(blockID);

#pragma endregion

#pragma region Mouse Logic
    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
    int blockX       = (int)floor(worldPos.x);
    int blockY       = (int)floor(worldPos.y);

    if ( !ImGui::IsWindowHovered() || !ImGui::IsWindowFocused() ) {
        if ( IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) {
            auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
            if ( b ) {
                b->type = blockType;
            }
        }

        if ( IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ) {
            auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
            if ( b ) {
                *b = {};
            }
        }
    }

    endDebugMenu();
#pragma endregion

    BeginMode2D(gameData.camera);

    Vector2 topLeftView     = GetScreenToWorld2D({0, 0}, gameData.camera);
    Vector2 bottomRightView = GetScreenToWorld2D(
        {(float)GetScreenWidth(), (float)GetScreenHeight()}, gameData.camera);

    int startXView = (int)floorf(topLeftView.x - 1);
    int endXView   = (int)ceilf(bottomRightView.x + 1);
    int startYView = (int)floorf(topLeftView.y - 1);
    int endYView   = (int)ceilf(bottomRightView.y + 1);

    startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
    endXView   = Clamp(endXView, 0, bottomRightView.x - 1);
    startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
    endYView   = Clamp(endYView, 0, bottomRightView.y - 1);

    for ( int y = startYView; y <= endYView; y++ ) {
        for ( int x = startXView; x <= endXView; x++ ) {
            auto &b = gameData.gameMap.getBlockUnsafe(x, y);

            if ( b.type == Block::Type::air ) {
                continue;
            }

            Texture2D texture = b.type == Block::Type::woodLog
                                    ? assetManager.tree
                                    : assetManager.textures;

            DrawTexturePro(texture, getTextureAtlas(b.type, 0, 32, 32),
                           {(float)x, (float)y, 1.f, 1.f}, {0.f, 0.f}, 0.f,
                           WHITE);
        }
    }

    DrawTexturePro(assetManager.frame,
                   {0, 0, (float)assetManager.frame.width,
                    (float)assetManager.frame.height},
                   {(float)blockX, (float)blockY, 1, 1}, {}, 0.f, WHITE);

    EndMode2D();

    return true;
}

void closeGame() {
    std::ofstream f(RESOURCES_PATH "f.txt");
    f << "\nCLOSED\n";
    f.close();
}

void startDebugMenu(char *id, const size_t idSize, uint16_t *blockID) {
    ImGui::Begin("Debug Menu");
    ImGui::Text("Block ID: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(110.f);
    ImGui::InputTextWithHint("###ID", "0 - 53", id, 3);
    ImGui::SameLine();
    if ( ImGui::SmallButton("Clear") ) {
        id[0]    = '\0';
        *blockID = 0;
    }
    if ( strlen(id) > 0 ) {
        try {
            *blockID = static_cast<uint16_t>(std::stoi(id));
        } catch ( std::invalid_argument const &e ) {
            id[0]    = '\0';
            *blockID = 0;
        }
    }
    *blockID = std::min(*blockID, (uint16_t)(Block::BLOCKS_COUNT - 1));
}

void endDebugMenu() { ImGui::End(); }

};  // namespace GameLayer
