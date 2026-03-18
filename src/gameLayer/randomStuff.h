#pragma once
#include <random>

namespace GameLayer {
float getRandomFloat(std::ranlux24_base &rng, float min, float max);

int getRandomInt(std::ranlux24_base &rng, int min, int max);

bool getRandomChance(std::ranlux24_base &rng, float chance);
};  // namespace GameLayer
