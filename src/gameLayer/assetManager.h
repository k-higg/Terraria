#pragma once
#include <raylib.h>

namespace GameLayer {

struct AssetManager {
#pragma region Player sprites
    Texture2D player        = {};
    Texture2D playerSprites = {};
    Texture2D items         = {};
    Texture2D hearts        = {};

    Texture2D frame = {};
#pragma endregion
#pragma region Environment sprites
    Texture2D dirt               = {};
    Texture2D textures           = {};
    Texture2D backgroundTextures = {};
    Texture2D treeTextures       = {};
    Texture2D caveBG             = {};
    Texture2D desertBG           = {};
    Texture2D forestBG           = {};
    Texture2D snowBG             = {};
#pragma endregion
#pragma region Enemy sprites
    Texture2D blueSlime      = {};
    Texture2D evilEye        = {};
    Texture2D iceSlime       = {};
    Texture2D mummy          = {};
    Texture2D slime          = {};
    Texture2D smallBlueSlime = {};
    Texture2D zombieEskimo   = {};
    Texture2D zombie         = {};
#pragma endregion

    void loadAll();
};

}  // namespace GameLayer
