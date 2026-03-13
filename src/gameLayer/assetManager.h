#pragma once
#include <raylib.h>

namespace GameLayer {

struct AssetManager {
    Texture2D dirt     = {};
    Texture2D textures = {};
    Texture2D frame    = {};
    Texture2D tree     = {};

    void loadAll();
};

}  // namespace GameLayer
