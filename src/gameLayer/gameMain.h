#pragma once

#include <cstddef>
#include <cstdint>

namespace GameLayer {
bool initGame();
bool updateGame();
void closeGame();

void startDebugMenu(char *_blockID, const size_t idSize, uint16_t *blockID,
                    char *_wallID, const size_t wallIDSize, uint16_t *wallID);

void endDebugMenu();

};  // namespace GameLayer
