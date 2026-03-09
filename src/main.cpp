#include <imgui.h>
#include <raylib.h>
#include <rlImgui.h>

typedef struct Window {
    int width;
    int height;
    char *title;
} window_t;

int main() {
    window_t window = {.width = 800, .height = 450, .title = "Test"};
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(window.width, window.height, window.title);

#pragma region Imgui
    rlImGuiSetup(true);

    ImGuiIO &io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard
    // Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnabledGamepad; // Enable
    // gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.FontGlobalScale = 2.5;
#pragma endregion

    Rectangle rect_one = {.width = 50, .height = 50, .x = 100, .y = 100};
    Rectangle rect_two = {.width = 75, .height = 75, .x = 100, .y = 100};

    while ( !WindowShouldClose() ) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

#pragma region Imgui
        rlImGuiBegin();

        // Docking stuff
        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);
#pragma endregion

        DrawRectangleRec(rect_one, {0, 255, 0, 127});
        DrawRectangleRec(rect_two, {255, 0, 0, 127});

        rect_one.x += 100 * GetFrameTime();

#pragma region Imgui Windows
        ImGui::Begin("test");
        ImGui::Text("Hello");
        ImGui::Button("button");
        ImGui::ShowDemoWindow();
        ImGui::End();
        rlImGuiEnd();
#pragma endregion

        EndDrawing();
    }

#pragma region Imgui
    rlImGuiShutdown();
#pragma endregion

    CloseWindow();

    return 0;
}
