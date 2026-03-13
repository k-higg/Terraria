#pragma once
#include <raylib.h>

namespace GameLayer {

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX,
                          int cellSizePixelsY);

}  // namespace GameLayer
