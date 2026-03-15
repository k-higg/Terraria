#include "assetManager.h"

namespace GameLayer {

void AssetManager::loadAll() {
#pragma region Player sprites
    player        = LoadTexture(RESOURCES_PATH "player.png");
    playerSprites = LoadTexture(RESOURCES_PATH "playerSprites.png");
    items         = LoadTexture(RESOURCES_PATH "items.png");
    hearts        = LoadTexture(RESOURCES_PATH "hearts.png");

    frame = LoadTexture(RESOURCES_PATH "frame.png");
#pragma endregion
#pragma region Environment sprites
    dirt     = LoadTexture(RESOURCES_PATH "dirt.png");
    textures = LoadTexture(RESOURCES_PATH "textures.png");
    backgroundTextures =
        LoadTexture(RESOURCES_PATH "texturesWithBackgroundVersion.png");
    treeTextures = LoadTexture(RESOURCES_PATH "treetextures.png");
    caveBG       = LoadTexture(RESOURCES_PATH "caveBG.png");
    desertBG     = LoadTexture(RESOURCES_PATH "desertBG.png");
    forestBG     = LoadTexture(RESOURCES_PATH "forestBG.png");
    snowBG       = LoadTexture(RESOURCES_PATH "snowBG.png");
#pragma endregion
#pragma region Enemy sprites
    blueSlime      = LoadTexture(RESOURCES_PATH "blueslime.png");
    evilEye        = LoadTexture(RESOURCES_PATH "evilEye.png");
    iceSlime       = LoadTexture(RESOURCES_PATH "iceslime.png");
    mummy          = LoadTexture(RESOURCES_PATH "mummy.png");
    slime          = LoadTexture(RESOURCES_PATH "slime.png");
    smallBlueSlime = LoadTexture(RESOURCES_PATH "smallblueslime.png");
    zombieEskimo   = LoadTexture(RESOURCES_PATH "zombie_eskimo.png");
    zombie         = LoadTexture(RESOURCES_PATH "zombie.png");

#pragma endregion
}

}  // namespace GameLayer
