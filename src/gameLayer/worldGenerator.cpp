#include "worldGenerator.h"

#include <cmath>

#include "randomStuff.h"

namespace GameLayer {

void generateWorld(GameMap &gameMap, int seed) {
    const int w = 900;
    const int h = 500;

    gameMap.create(w, h);

    int dirtSizeMin  = 0;
    int dirtSizeMax  = 50;
    int stoneSizeMin = 380;
    int stoneSizeMax = 430;

    int dirtSize    = 50;
    int stoneSize   = 380;
    int targetDirt  = dirtSize;
    int targetStone = stoneSize;

    std::ranlux24_base rng(seed);

    int nextTargetX       = 0;
    const float smoothing = 0.08f;  // lower == smoother

    for ( int x = 0; x < w; x++ ) {
        if ( x >= nextTargetX ) {
            nextTargetX = x + 50;

            if ( getRandomFloat(rng, 0, 1) < 0.5f ) {
                targetDirt = 0;
            } else {
                targetDirt = static_cast<int>(
                    getRandomFloat(rng, dirtSizeMin, dirtSizeMax));
            }
            targetStone = static_cast<int>(
                getRandomFloat(rng, stoneSizeMin, stoneSizeMax));
        }

        dirtSize += static_cast<int>((targetDirt - dirtSize) * smoothing);
        stoneSize += static_cast<int>((targetStone - stoneSize) * smoothing);
        int targetY = h - (dirtSize + stoneSize);

        for ( int y = 0; y < h; y++ ) {
            Block b;

            if ( y < targetY ) {
                b.type = Block::Type::air;
            } else if ( y == targetY && dirtSize >= 1 ) {
                b.type = Block::Type::grassBlock;
            } else if ( y < h - stoneSize ) {
                b.type = Block::Type::dirt;
            } else {
                b.type = Block::Type::stone;

                if ( getRandomChance(rng, 0.05) ) {
                    b.type = Block::Type::gold;
                }
            }

            gameMap.getBlockUnsafe(x, y) = b;
        }
    }
}
};  // namespace GameLayer
