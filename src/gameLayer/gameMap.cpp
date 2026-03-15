#include "gameMap.h"

#include "asserts.h"

namespace GameLayer {

void GameMap::create(int w, int h) {
    *this = {};  // Reset all data

    mapData.resize(w * h);
    wallData.resize(w * h);

    this->w = w;
    this->h = h;

    for ( auto &e : mapData ) {
        e = {};
    }  // Clears all block data

    for ( auto &e : wallData ) {
        e = {};
    }
}

Block &GameMap::getBlockUnsafe(int x, int y) {
    permaAssertCommentDevelopement(mapData.size() == w * h,
                                   "Map data not initialized");

    permaAssertCommentDevelopement(x >= 0 && y >= 0 && x < w && y < h,
                                   "GetBlockUnsafe out of bounds error");

    return mapData[x + y * w];
}

Block *GameMap::getBlockSafe(int x, int y) {
    permaAssertCommentDevelopement(mapData.size() == w * h,
                                   "Map data not initialized");

    if ( x < 0 || y < 0 || x >= w || y >= h ) {
        return nullptr;
    }

    return &mapData[x + y * w];
}

Block &GameMap::getWallUnsafe(int x, int y) {
    permaAssertCommentDevelopement(wallData.size() == w * h,
                                   "Wall data not initialized");

    permaAssertCommentDevelopement(x >= 0 && y >= 0 && x < w && y < h,
                                   "GetBlockUnsafe out of bounds error");

    return wallData[x + y * w];
}

Block *GameMap::getWallSafe(int x, int y) {
    permaAssertCommentDevelopement(wallData.size() == w * h,
                                   "Wall data not initialized");

    if ( x < 0 || y < 0 || x >= w || y >= h ) {
        return nullptr;
    }

    return &wallData[x + y * w];
}
}  // namespace GameLayer
