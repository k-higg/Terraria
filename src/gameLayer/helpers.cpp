#include "helpers.h"

namespace GameLayer {

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX,
                          int cellSizePixelsY) {
    return Rectangle{(float)x * cellSizePixelsX, (float)y * cellSizePixelsY,
                     (float)cellSizePixelsX, (float)cellSizePixelsY};
}

}  // namespace GameLayer
