#include <raylib.h>

#include "gameMain.h"
#include "imguiMain.h"

typedef struct Window {
    int width;
    int height;
    char *title;
} window_t;

int main() {
#if PRODUCTION_BUILD == 1
    SetTraceLogLevel(LOG_NONE);
#endif

    window_t window = {1280, 720, (char *)"Test"};
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(window.width, window.height, window.title);
    SetExitKey(KEY_NULL);  // Disable Esc from closing window
    SetTargetFPS(240);

    Overlay::initImGui();

    if ( !GameLayer::initGame() ) {
        return 1;
    }

    while ( !WindowShouldClose() ) {
        BeginDrawing();
        ClearBackground(BLACK);

        Overlay::beginImGui();

        if ( !GameLayer::updateGame() ) {
            CloseWindow();
        }

        Overlay::endImGui();
        EndDrawing();
    }

    Overlay::shutdownImGui();

    CloseWindow();
    GameLayer::closeGame();

    return 0;
}
