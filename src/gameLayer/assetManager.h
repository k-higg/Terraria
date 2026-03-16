#pragma once
#include <raylib.h>

namespace GameLayer {

struct AssetManager {
#pragma region Player sprites
    Texture2D player           = {};
    Texture2D playerSprites    = {};
    Texture2D items            = {};
    Texture2D hearts           = {};
    Texture2D copperArmorBack  = {};
    Texture2D copperArmorFeet  = {};
    Texture2D copperArmorFront = {};
    Texture2D copperArmorHead  = {};
    Texture2D goldArmorBack    = {};
    Texture2D goldArmorFeet    = {};
    Texture2D goldArmorFront   = {};
    Texture2D goldArmorHead    = {};
    Texture2D iceArmorBack     = {};
    Texture2D iceArmorFeet     = {};
    Texture2D iceArmorFront    = {};
    Texture2D iceArmorHead     = {};
    Texture2D ironArmorBack    = {};
    Texture2D ironArmorFeet    = {};
    Texture2D ironArmorFront   = {};
    Texture2D ironArmorHead    = {};
    Texture2D partyHat         = {};
    Texture2D playerBack       = {};
    Texture2D playerFeet       = {};
    Texture2D playerFront      = {};
    Texture2D playerHead       = {};
    Texture2D sunglasses       = {};
    Texture2D thumbs           = {};

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

#pragma region Music
    Music bonus   = {};
    Music cave    = {};
    Music credits = {};
    Music desert  = {};
    Music forest  = {};
    Music snow    = {};
#pragma endregion

#pragma region Sounds
    Sound breakSound  = {};
    Sound place       = {};
    Sound backButton  = {};
    Sound buttonPress = {};
    Sound checkBoxOff = {};
    Sound checkBoxOn  = {};
    Sound finalHit1   = {};
    Sound finalHit2   = {};
    Sound finalHit3   = {};
    Sound hImpact1    = {};
    Sound hImpact2    = {};
    Sound hImpact3    = {};
    Sound hit1        = {};
    Sound hit2        = {};
    Sound hit3        = {};
    Sound slider      = {};
    Sound stone1      = {};
    Sound stone2      = {};
    Sound stone3      = {};
    Sound stone4      = {};
    Sound stone5      = {};
    Sound stone6      = {};
    Sound stone7      = {};
    Sound wood1       = {};
    Sound wood2       = {};
    Sound wood3       = {};
    Sound wood4       = {};
    Sound wood5       = {};
    Sound wood6       = {};
    Sound wood7       = {};
#pragma endregion

    void loadAll();
};

}  // namespace GameLayer
