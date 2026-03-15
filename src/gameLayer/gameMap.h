#pragma once
#include <vector>

#include "blocks.h"

namespace GameLayer {

struct GameMap {
    int w = 0;
    int h = 0;

    std::vector<Block> mapData;
    std::vector<Wall> wallData;

    void create(int w, int h);

    Block &getBlockUnsafe(int x, int y);
    Block *getBlockSafe(int x, int y);

    Wall &getWallUnsafe(int x, int y);
    Wall *getWallSafe(int x, int y);
};

}  // namespace GameLayer
