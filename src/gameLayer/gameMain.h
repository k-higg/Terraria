#pragma once

#include <cstddef>
#include <cstdint>

namespace GameLayer {
bool initGame();
bool updateGame();
void closeGame();

void startDebugMenu(char *id, const size_t idSize, uint16_t *blockID);
void endDebugMenu();

};  // namespace GameLayer
