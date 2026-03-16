#include "assetManager.h"

namespace GameLayer {

void AssetManager::loadAll() {
#pragma region Player sprites
    player          = LoadTexture(RESOURCES_PATH "player.png");
    playerSprites   = LoadTexture(RESOURCES_PATH "playerSprites.png");
    items           = LoadTexture(RESOURCES_PATH "items.png");
    hearts          = LoadTexture(RESOURCES_PATH "hearts.png");
    copperArmorBack = LoadTexture(RESOURCES_PATH "body/copper_armour_back.png");
    copperArmorFeet = LoadTexture(RESOURCES_PATH "body/copper_armour_feet.png");
    copperArmorFront =
        LoadTexture(RESOURCES_PATH "body/copper_armour_front.png");
    copperArmorFeet = LoadTexture(RESOURCES_PATH "body/copper_armour_head.png");
    goldArmorBack   = LoadTexture(RESOURCES_PATH "body/gold_armour_back.png");
    goldArmorFeet   = LoadTexture(RESOURCES_PATH "body/gold_armour_feet.png");
    goldArmorFront  = LoadTexture(RESOURCES_PATH "body/gold_armour_front.png");
    goldArmorHead   = LoadTexture(RESOURCES_PATH "body/gold_armour_head.png");
    iceArmorBack    = LoadTexture(RESOURCES_PATH "body/ice_armour_back.png");
    iceArmorFeet    = LoadTexture(RESOURCES_PATH "body/ice_armour_feet.png");
    iceArmorFront   = LoadTexture(RESOURCES_PATH "body/ice_armour_front.png");
    iceArmorHead    = LoadTexture(RESOURCES_PATH "body/ice_armour_head.png");
    ironArmorBack   = LoadTexture(RESOURCES_PATH "body/iron_armour_back.png");
    ironArmorFeet   = LoadTexture(RESOURCES_PATH "body/iron_armour_feet.png");
    ironArmorFront  = LoadTexture(RESOURCES_PATH "body/iron_armour_front.png");
    ironArmorHead   = LoadTexture(RESOURCES_PATH "body/iron_armour_head.png");
    partyHat        = LoadTexture(RESOURCES_PATH "body/party_hat");
    playerBack      = LoadTexture(RESOURCES_PATH "body/player_back.png");
    playerFeet      = LoadTexture(RESOURCES_PATH "body/player_feet.png");
    playerFront     = LoadTexture(RESOURCES_PATH "body/player_front.png");
    playerHead      = LoadTexture(RESOURCES_PATH "body/player_head.png");
    sunglasses      = LoadTexture(RESOURCES_PATH "body/sunglasses.png");
    thumbs          = LoadTexture(RESOURCES_PATH "body/Thumbs.png");
    frame           = LoadTexture(RESOURCES_PATH "frame.png");
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

#pragma region Music
    bonus   = LoadMusicStream(RESOURCES_PATH "/music/bonus.ogg");
    cave    = LoadMusicStream(RESOURCES_PATH "/music/cave.ogg");
    credits = LoadMusicStream(RESOURCES_PATH "/music/Credits.ogg");
    desert  = LoadMusicStream(RESOURCES_PATH "/music/desert.ogg");
    forest  = LoadMusicStream(RESOURCES_PATH "/music/forest.ogg");
    snow    = LoadMusicStream(RESOURCES_PATH "/music/snow.ogg");
#pragma endregion
#pragma region Sound
    breakSound  = LoadSound(RESOURCES_PATH "sounds/break.ogg");
    place       = LoadSound(RESOURCES_PATH "sounds/place.ogg");
    backButton  = LoadSound(RESOURCES_PATH "sounds/bonus/BackButton.ogg");
    buttonPress = LoadSound(RESOURCES_PATH "sounds/bonus/ButtonPress.ogg");
    checkBoxOff = LoadSound(RESOURCES_PATH "sounds/bonus/CheckBoxOff.ogg");
    checkBoxOn  = LoadSound(RESOURCES_PATH "sounds/bonus/CheckBoxOn.ogg");
    finalHit1   = LoadSound(RESOURCES_PATH "sounds/bonus/FinalHit1.ogg");
    finalHit2   = LoadSound(RESOURCES_PATH "sounds/bonus/FinalHit2.ogg");
    finalHit3   = LoadSound(RESOURCES_PATH "sounds/bonus/FinalHit3.ogg");
    hImpact1    = LoadSound(RESOURCES_PATH "sounds/bonus/HImpact1.ogg");
    hImpact2    = LoadSound(RESOURCES_PATH "sounds/bonus/HImpact2.ogg");
    hImpact3    = LoadSound(RESOURCES_PATH "sounds/bonus/HImpact3.ogg");
    hit1        = LoadSound(RESOURCES_PATH "sounds/bonus/Hit1.ogg");
    hit2        = LoadSound(RESOURCES_PATH "sounds/bonus/Hit2.ogg");
    hit3        = LoadSound(RESOURCES_PATH "sounds/bonus/Hit3.ogg");
    slider      = LoadSound(RESOURCES_PATH "sounds/bonus/Slider.ogg");
    stone1      = LoadSound(RESOURCES_PATH "sounds/bonus/Stone1.ogg");
    stone2      = LoadSound(RESOURCES_PATH "sounds/bonus/Stone2.ogg");
    stone3      = LoadSound(RESOURCES_PATH "sounds/bonus/Stone3.ogg");
    stone4      = LoadSound(RESOURCES_PATH "sounds/bonus/Stone4.ogg");
    stone5      = LoadSound(RESOURCES_PATH "sounds/bonus/Stone5.ogg");
    stone6      = LoadSound(RESOURCES_PATH "sounds/bonus/Stone6.ogg");
    stone7      = LoadSound(RESOURCES_PATH "sounds/bonus/Stone7.ogg");
    wood1       = LoadSound(RESOURCES_PATH "sounds/bonus/Wood1.ogg");
    wood2       = LoadSound(RESOURCES_PATH "sounds/bonus/Wood2.ogg");
    wood3       = LoadSound(RESOURCES_PATH "sounds/bonus/Wood3.ogg");
    wood4       = LoadSound(RESOURCES_PATH "sounds/bonus/Wood4.ogg");
    wood5       = LoadSound(RESOURCES_PATH "sounds/bonus/Wood5.ogg");
    wood6       = LoadSound(RESOURCES_PATH "sounds/bonus/Wood6.ogg");
    wood7       = LoadSound(RESOURCES_PATH "sounds/bonus/Wood7.ogg");
#pragma endregion
}

}  // namespace GameLayer
