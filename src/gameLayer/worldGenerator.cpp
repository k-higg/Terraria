#include "worldGenerator.h"

#include <FastNoiseSIMD.h>
#include <raymath.h>

#include <memory>

#include "randomStuff.h"

namespace GameLayer {

void generateWorld(GameMap &gameMap, int seed) {
    const int w = 900;
    const int h = 500;

    gameMap.create(w, h);


    std::ranlux24_base rng(seed++);

    const std::unique_ptr<FastNoiseSIMD> dirtNoiseGenerator(
        FastNoiseSIMD::NewFastNoiseSIMD());
    const std::unique_ptr<FastNoiseSIMD> caveNoiseGenerator(FastNoiseSIMD::NewFastNoiseSIMD());

    dirtNoiseGenerator->SetSeed(seed++);
    caveNoiseGenerator->SetSeed(seed++);

    dirtNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
    dirtNoiseGenerator->SetFractalOctaves(6);
    dirtNoiseGenerator->SetFractalGain(0.04f);
    dirtNoiseGenerator->SetFrequency(0.02f);

    caveNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
    caveNoiseGenerator->SetFractalOctaves(3);
    caveNoiseGenerator->SetFrequency(0.02f);

    float *dirtNoise  = FastNoiseSIMD::GetEmptySet(w);
    float *caveNoise  = FastNoiseSIMD::GetEmptySet(w * h);

    dirtNoiseGenerator->FillNoiseSet(dirtNoise, 0, 0, 0, w, 1, 1);
    caveNoiseGenerator->FillNoiseSet(caveNoise, 0, 0, 0, h, w, 1);

    // convert from [-1 +] to [0 1]
    for ( int i = 0; i < w; i++ ) {
        dirtNoise[i]  = (dirtNoise[i] + 1) / 2;
    }

    // convert from [-1 +] to [0 1]
    for (int i{}; i < w * h; i++ ) {
        caveNoise[i]  = (caveNoise[i] + 1) / 2;
    }

    auto getCaveNoise = [&](const int x, const int y) {
      return caveNoise[x + y * w];
    };

    constexpr int dirtOffsetStart = -5;
    constexpr int dirtOffsetEnd   = 35;

    constexpr int stoneHeightStart = 60;
    constexpr int stoneHeightEnd = 120;

    constexpr int desertWidthMin = 100;
    constexpr int desertWidthMax = 100;

    constexpr int dirStoneMin = -2;
    constexpr int dirStoneMax = 2;

    const int desertStart = getRandomInt(rng, desertWidthMin, w - 100);
    const int desertEnd = desertStart + desertWidthMax + getRandomInt(rng, 0, 100);

    int keepDirTimeStone = getRandomInt(rng, 5, 40);
    int dirStone = getRandomInt(rng, dirStoneMin, dirStoneMax);

    int stoneHeight = 90;

    for ( int x = 0; x < w; x++ ) {

        bool inDesert = (x >= desertStart && x <= desertEnd);

#pragma region Stone Height
        keepDirTimeStone--;

        if ( keepDirTimeStone <= 0 ) {
            keepDirTimeStone = getRandomInt(rng, 5, 40);
            dirStone = getRandomInt(rng, dirStoneMin, dirStoneMax);
        }

        if (dirStone == -1) {
            if (getRandomChance(rng, 0.25)) {
                stoneHeight--;
            }
        } else if (dirStone == -2) {
            for (int i{}; i < 2; i++) {
                if (getRandomChance(rng, 0.25)) {
                    stoneHeight--;
                }
            }
        } else if (dirStone == 1) {
            if (getRandomChance(rng, 0.25)) {
                stoneHeight++;
            }
        } else if (dirStone == 2) {
            for (int i{}; i < 2; i++) {
                if (getRandomChance(rng, 0.25)) {
                    stoneHeight++;
                }
            }
        }

        if (stoneHeight < stoneHeightStart) {
            stoneHeight = stoneHeightStart;
        }

        if (stoneHeight > stoneHeightEnd) {
            stoneHeight = stoneHeightEnd;
        }

#pragma endregion

        int dirtHeight = (int)Lerp((float)dirtOffsetStart, (float)dirtOffsetEnd,
                                   (float)dirtNoise[x]);
        dirtHeight = stoneHeight - dirtHeight;

        int dirtType = Block::Type::dirt;
        int grassType = Block::Type::grass;
        int stoneType = Block::Type::stone;

        if (inDesert) {
            dirtType = Block::Type::sand;
            grassType = Block::Type::sand;
            stoneType = Block::Type::sandStone;
        }

        for ( int y = 0; y < h; y++ ) {
            Block b;

            if ( y > dirtHeight ) {
                b.type = (Block::Type)dirtType;
            }
            if ( y == dirtHeight ) {
                b.type = (Block::Type)grassType;
            }
            if ( y >= stoneHeight ) {
                b.type = (Block::Type)stoneType;
            }

            if (inDesert) {
                const int desertMid = (desertStart + desertEnd) / 2;
                const int desertHalfWidth = (desertEnd - desertStart) / 2;
                const int distFromDesertMid = std::abs(x - desertMid);

                const float desertDist = 1 - distFromDesertMid / (float)desertHalfWidth;

                const int desertStoneStart = 10 + stoneHeight;
                const int desertStoneDepth = 20 + stoneHeight;

                const int triangleStoneY = desertStoneStart + desertDist * desertStoneDepth;

                if (y > triangleStoneY) {
                    b.type = Block::Type::stone;
                }
            }

            // bigger more interesting caves
            // getCaveNoise(x,y) < 0.8f &&& getCaveNoise(x,y) > 0.6f

            if ( getCaveNoise(x, y) < 0.3f) {
                b.type = Block::Type::air;
            }

            gameMap.getBlockUnsafe(x, y) = b;
        }
    }

    FastNoiseSIMD::FreeNoiseSet(dirtNoise);
    FastNoiseSIMD::FreeNoiseSet(caveNoise);
}
};  // namespace GameLayer
