#pragma once

#include <cstddef>
#include <cstdint>

#include "raylib.h"

namespace GameLayer {
bool initGame();
bool updateGame();
void closeGame();

void renderTree(Texture2D texture, int x, int y);

void startDebugMenu(char *id, const size_t idSize, uint16_t *blockID);
void endDebugMenu();

};  // namespace GameLayer
