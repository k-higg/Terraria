#include "gameMain.h"

#include <imgui.h>
#include <raylib.h>
#include <raymath.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "assetManager.h"
#include "gameMap.h"
#include "helpers.h"
#include "randomStuff.h"
#include "worldGenerator.h"

namespace GameLayer {

#pragma region Variables

struct GameData {
    GameMap gameMap;
    Camera2D camera = {};
} gameData;

struct UIData {
    ImVec2 uiPos;
    ImVec2 uiSize;
} uiData;

bool mouseOverUI = false;

AssetManager assetManager;
unsigned seed = static_cast<unsigned>(std::time(nullptr));
std::ranlux24_base rng(seed);

#pragma endregion

bool initGame() {
    assetManager.loadAll();

    generateWorld(gameData.gameMap, seed);

    gameData.camera.target   = {20, 120};
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
    static float CAMERA_SPEED = 10.f;
    if ( IsKeyDown(KEY_UP) ) {
        gameData.camera.target.y -= CAMERA_SPEED * deltaTime;
    }
    if ( IsKeyDown(KEY_LEFT) ) {
        gameData.camera.target.x -= CAMERA_SPEED * deltaTime;
    }
    if ( IsKeyDown(KEY_DOWN) ) {
        gameData.camera.target.y += CAMERA_SPEED * deltaTime;
    }
    if ( IsKeyDown(KEY_RIGHT) ) {
        gameData.camera.target.x += CAMERA_SPEED * deltaTime;
    }
#pragma endregion

#pragma region Block Selector
    static char id[3]            = "";
    static uint16_t blockID      = 0;
    static Block::Type blockType = Block::Type::air;
    blockType                    = static_cast<Block::Type>(blockID);
#pragma endregion

#pragma region Mouse Logic
    const Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
    const int blockX       = (int)floor(worldPos.x);
    const int blockY       = (int)floor(worldPos.y);

    if ( !mouseOverUI ) {
        if ( IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) {
            std::cout << "X: " << blockX << " Y: " << blockY << std::endl;
            if ( blockID > 53 && blockID <= Block::Type::BLOCKS_COUNT - 1 ) {
                auto w = gameData.gameMap.getWallSafe(blockX, blockY);
                if ( w ) {
                    w->type    = blockType;
                    w->variant = getRandomInt(rng, 0, 3);
                }
            } else {
                auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
                if ( b ) {
                    b->type    = blockType;
                    b->variant = getRandomInt(rng, 0, 3);
                }
            }
        }

        if ( IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ) {
            if ( IsKeyDown(KEY_LEFT_SHIFT) ) {
                auto w = gameData.gameMap.getWallSafe(blockX, blockY);
                if ( w ) {
                    *w = {};
                }
            } else {
                auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
                if ( b ) {
                    *b = {};
                }
            }
        }
    }
#pragma endregion

#pragma region Rendering
    BeginMode2D(gameData.camera);

    Vector2 topLeftView     = GetScreenToWorld2D({0, 0}, gameData.camera);
    Vector2 bottomRightView = GetScreenToWorld2D(
        {(float)GetScreenWidth(), (float)GetScreenHeight()}, gameData.camera);

    int startXView = (int)floorf(topLeftView.x - 1);
    int endXView   = (int)ceilf(bottomRightView.x + 1);
    int startYView = (int)floorf(topLeftView.y - 1);
    int endYView   = (int)ceilf(bottomRightView.y + 1);

    startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
    endXView   = Clamp(endXView, 0, gameData.gameMap.w - 1);
    startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
    endYView   = Clamp(endYView, 0, gameData.gameMap.h - 1);

    for ( int y = startYView; y <= endYView; y++ ) {
        for ( int x = startXView; x <= endXView; x++ ) {
            auto &b = gameData.gameMap.getBlockUnsafe(x, y);
            auto &w = gameData.gameMap.getWallUnsafe(x, y);

            DrawTexturePro(assetManager.backgroundTextures,
                           getTextureAtlas(w.type, w.variant, 32, 32),
                           {(float)x, (float)y, 1, 1}, {0.f, 0.f}, 0.f, WHITE);

            if ( b.type != Block::Type::air ) {
                DrawTexturePro(
                    assetManager.textures, getTextureAtlas(b.type, 0, 32, 32),
                    {(float)x, (float)y, 1.f, 1.f}, {0.f, 0.f}, 0.f, WHITE);
            }
        }
    }

    DrawTexturePro(assetManager.frame,
                   {0, 0, (float)assetManager.frame.width,
                    (float)assetManager.frame.height},
                   {(float)blockX, (float)blockY, 1, 1}, {}, 0.f, WHITE);
    EndMode2D();

#pragma endregion

#pragma region Debug Menu

    ImGui::Begin("Debug Menu");
    ImGui::Text("Block ID: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(110.f);
    ImGui::InputTextWithHint("###blockID", "0 - 71", id, 3);
    ImGui::SameLine();
    if ( ImGui::SmallButton("Clear####blockIDclear") ) {
        id[0]   = '\0';
        blockID = 0;
    }
    if ( strlen(id) > 0 ) {
        try {
            blockID = static_cast<uint16_t>(std::stoi(id));
        } catch ( std::invalid_argument const &e ) {
            id[0]   = '\0';
            blockID = 0;
        }
    }
    blockID = std::min(blockID, (uint16_t)(Block::BLOCKS_COUNT - 1));
    ImGui::Text("Camera Zoom: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(150.f);
    ImGui::SliderFloat("###Camera Zoom", &gameData.camera.zoom, 1.f, 100.f);
    ImGui::Text("Camera Speed: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(150.f);
    ImGui::SliderFloat("###Camera Speed", &CAMERA_SPEED, 5, 150);

    uiData.uiPos = ImGui::GetWindowPos();
    uiData.uiSize = ImGui::GetWindowSize();

    mouseOverUI = ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup);

    ImGui::End();

#pragma endregion

    DrawFPS(10, 10);

    return true;
}

void closeGame() {
    std::ofstream f(RESOURCES_PATH "f.txt");
    f << "\nCLOSED\n";
    f.close();
}

};  // namespace GameLayer
