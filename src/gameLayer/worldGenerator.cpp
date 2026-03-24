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

    std::ranlux24_base rng(seed);

    std::unique_ptr<FastNoiseSIMD> dirtNoiseGenerator(
        FastNoiseSIMD::NewFastNoiseSIMD());
    std::unique_ptr<FastNoiseSIMD> stoneNoiseGenerator(
        FastNoiseSIMD::NewFastNoiseSIMD());

    dirtNoiseGenerator->SetSeed(seed++);
    stoneNoiseGenerator->SetSeed(seed++);

    dirtNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
    dirtNoiseGenerator->SetFractalOctaves(1);
    dirtNoiseGenerator->SetFrequency(0.02);

    stoneNoiseGenerator->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
    stoneNoiseGenerator->SetFractalOctaves(4);
    stoneNoiseGenerator->SetFrequency(0.01);

    float *dirtNoise  = FastNoiseSIMD::GetEmptySet(w);
    float *stoneNoise = FastNoiseSIMD::GetEmptySet(w);

    dirtNoiseGenerator->FillNoiseSet(dirtNoise, 0, 0, 0, w, 1, 1);
    stoneNoiseGenerator->FillNoiseSet(stoneNoise, 0, 0, 0, w, 1, 1);

    // convert from [-1 +] to [0 1]
    for ( int i = 0; i < w; i++ ) {
        dirtNoise[i]  = (dirtNoise[i] + 1) / 2;
        stoneNoise[i] = (stoneNoise[i] + 1) / 2;

        // stoneNoise[i] = std::pow(stoneNoise[i], 2); //  steeper mountains
    }

    int dirtOffsetStart = -5;
    int dirtOffsetEnd   = 35;

    int stoneHeightStart = 80;
    int stoneHeightEnd   = 170;

    for ( int x = 0; x < w; x++ ) {
        int dirtHeight = (int)Lerp((float)dirtOffsetStart, (float)dirtOffsetEnd,
                                   (float)dirtNoise[x]);
        int stoneHeight =
            (int)Lerp((float)stoneHeightStart, (float)stoneHeightEnd,
                      (float)stoneNoise[x]);
        dirtHeight = stoneHeight - dirtHeight;

        for ( int y = 0; y < h; y++ ) {
            Block b;

            if ( y > dirtHeight ) {
                b.type = Block::Type::dirt;
            }
            if ( y == dirtHeight ) {
                b.type = Block::Type::grassBlock;
            }
            if ( y >= stoneHeight ) {
                b.type = Block::Type::stone;
            }

            gameMap.getBlockUnsafe(x, y) = b;
        }
    }

    FastNoiseSIMD::FreeNoiseSet(dirtNoise);
    FastNoiseSIMD::FreeNoiseSet(stoneNoise);
}
};  // namespace GameLayer
