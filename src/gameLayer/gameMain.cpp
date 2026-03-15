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

    // if camera target is set to 0,0 you can't place blocks on like half of the screen
    gameData.camera.target   = {6, 3};
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
            if ( blockID > 53 && blockID <= Block::Type::BLOCKS_COUNT - 1 ) {
                auto w = gameData.gameMap.getWallSafe(blockX, blockY);
                if ( w ) {
                    w->type = blockType;
                }
            } else {
                auto b = gameData.gameMap.getBlockSafe(blockX, blockY);
                if ( b ) {
                    b->type = blockType;
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
    endDebugMenu();
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
    endXView   = Clamp(endXView, 0, bottomRightView.x - 1);
    startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
    endYView   = Clamp(endYView, 0, bottomRightView.y - 1);

    for ( int y = startYView; y <= endYView; y++ ) {
        for ( int x = startXView; x <= endXView; x++ ) {
            auto &b = gameData.gameMap.getBlockUnsafe(x, y);
            auto &w = gameData.gameMap.getWallUnsafe(x, y);

            DrawTexturePro(assetManager.backgroundTextures,
                           getTextureAtlas(w.type, 0, 32, 32),
                           {(float)x, (float)y, 1, 1}, {0.f, 0.f}, 0.f, WHITE);

            if ( b.type == Block::Type::air ) {
                continue;
            }

            Texture2D texture = b.type == Block::Type::woodLog
                                    ? assetManager.treeTextures
                                    : assetManager.textures;

            if ( b.type == Block::Type::woodLog ) {
                renderTree(texture, x, y);
            } else {
                DrawTexturePro(texture, getTextureAtlas(b.type, 0, 32, 32),
                               {(float)x, (float)y, 1.f, 1.f}, {0.f, 0.f}, 0.f,
                               WHITE);
            }
        }
    }

    DrawTexturePro(assetManager.frame,
                   {0, 0, (float)assetManager.frame.width,
                    (float)assetManager.frame.height},
                   {(float)blockX, (float)blockY, 1, 1}, {}, 0.f, WHITE);

    EndMode2D();
#pragma endregion

    return true;
}

void closeGame() {
    std::ofstream f(RESOURCES_PATH "f.txt");
    f << "\nCLOSED\n";
    f.close();
}

void renderTree(Texture2D texture, int x, int y) {
    auto blockAbove = gameData.gameMap.getBlockSafe(x, y - 1);
    auto blockLeft  = gameData.gameMap.getBlockSafe(x - 1, y);
    auto blockRight = gameData.gameMap.getBlockSafe(x + 1, y);
    auto blockBelow = gameData.gameMap.getBlockSafe(x, y + 1);
    if ( blockBelow->type == Block::Type::woodLog &&
         blockLeft->type == Block::Type::leaves &&
         blockRight->type == Block::Type::leaves &&
         blockAbove->type == Block::Type::leaves ) {
        DrawTexturePro(texture, getTextureAtlas(5, 0, 32, 32),
                       {(float)x, (float)y, 1.f, 1.f}, {0.f, 0.f}, 0.f, WHITE);
    } else if ( blockLeft->type == Block::Type::leaves &&
                blockRight->type == Block::Type::leaves &&
                blockBelow->type == Block::Type::woodLog ) {
        DrawTexturePro(texture, getTextureAtlas(1, 0, 32, 32),
                       {(float)x, (float)y, 1, 1}, {0.f, 0.f}, 0.f, WHITE);
    } else if ( blockLeft->type == Block::Type::leaves &&
                blockRight->type != Block::Type::leaves &&
                blockBelow->type == Block::Type::woodLog ) {
        DrawTexturePro(texture, getTextureAtlas(3, 0, 32, 32),
                       {(float)x, (float)y, 1, 1}, {0.f, 0.f}, 0.f, WHITE);
    } else if ( blockRight->type == Block::Type::leaves &&
                blockLeft->type != Block::Type::leaves &&
                blockBelow->type == Block::Type::woodLog ) {
        DrawTexturePro(texture, getTextureAtlas(2, 0, 32, 32),
                       {(float)x, (float)y, 1, 1}, {0.f, 0.f}, 0.f, WHITE);
    } else if ( blockBelow->type == Block::Type::woodLog ) {
        DrawTexturePro(texture, getTextureAtlas(0, 0, 32, 32),
                       {(float)x, (float)y, 1, 1}, {0.f, 0.f}, 0.f, WHITE);
    } else {
        DrawTexturePro(texture, getTextureAtlas(4, 0, 32, 32),
                       {(float)x, (float)y, 1, 1}, {0.f, 0.f}, 0.f, WHITE);
    }
}

void startDebugMenu(char *id, const size_t idSize, uint16_t *blockID) {
    ImGui::Begin("Debug Menu");
    ImGui::Text("Block ID: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(110.f);
    ImGui::InputTextWithHint("###blockID", "0 - 71", id, 3);
    ImGui::SameLine();
    if ( ImGui::SmallButton("Clear####blockIDclear") ) {
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
