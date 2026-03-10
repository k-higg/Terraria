#include <imgui.h>
#include <raylib.h>
#include <rlImgui.h>

#include <iostream>

void imgui_theme();

typedef struct Window {
    int width;
    int height;
    char *title;
} window_t;

int main() {
    window_t window = {.width = 1280, .height = 720, .title = "Test"};
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
    imgui_theme();
#pragma endregion

    Rectangle rect_one = {.width = 50, .height = 50, .x = 100, .y = 100};
    Rectangle rect_two = {.width = 75, .height = 75, .x = 100, .y = 100};

    while ( !WindowShouldClose() ) {
        BeginDrawing();
        ClearBackground(GRAY);

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
        ImGui::End();

        ImGui::Begin("second window");
        ImGui::Text("Speed");
        ImGui::SameLine();
        ImGui::TextDisabled("(?)");

        if ( ImGui::IsItemHovered() ) {
            ImGui::BeginTooltip();
            ImGui::Text("Controls how fast the player moves");
            ImGui::EndTooltip();
        }

        static char buffer[128] = "";

        ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsNoBlank |
                                    ImGuiInputTextFlags_EnterReturnsTrue |
                                    ImGuiInputTextFlags_AutoSelectAll;

        if ( ImGui::InputText("Player Name", buffer, sizeof(buffer), flags) ) {
            std::cout << "Confirmed name: " << buffer << std::endl;
        }
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

void imgui_theme() {
    ImGuiStyle &style    = ImGui::GetStyle();
    style.Alpha          = 1.0;
    style.ChildRounding  = 3;
    style.WindowRounding = 3;
    style.GrabRounding   = 1;
    style.GrabMinSize    = 20;
    style.FrameRounding  = 3;

    style.Colors[ImGuiCol_Text]           = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]   = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]        = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_Border]         = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow]   = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]        = ImVec4(0.44f, 0.80f, 0.80f, 0.18f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.44f, 0.80f, 0.80f, 0.27f);
    style.Colors[ImGuiCol_FrameBgActive]  = ImVec4(0.44f, 0.81f, 0.86f, 0.66f);
    style.Colors[ImGuiCol_TitleBg]        = ImVec4(0.14f, 0.18f, 0.21f, 0.73f);
    style.Colors[ImGuiCol_TitleBgCollapsed] =
        ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
    style.Colors[ImGuiCol_MenuBarBg]     = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    style.Colors[ImGuiCol_ScrollbarBg]   = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] =
        ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] =
        ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    // style.Colors[ImGuiCol_ComboBg]    = ImVec4(0.16f, 0.24f, 0.22f, 0.60f);
    style.Colors[ImGuiCol_CheckMark]  = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
    style.Colors[ImGuiCol_SliderGrabActive] =
        ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
    style.Colors[ImGuiCol_Button]        = ImVec4(0.00f, 0.65f, 0.65f, 0.46f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.01f, 1.00f, 1.00f, 0.43f);
    style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.00f, 1.00f, 1.00f, 0.62f);
    style.Colors[ImGuiCol_Header]        = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
    style.Colors[ImGuiCol_HeaderActive]  = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
    // style.Colors[ImGuiCol_Column]        = ImVec4(0.00f, 0.50f, 0.50f,
    // 0.33f); style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.00f, 0.50f,
    // 0.50f, 0.47f); style.Colors[ImGuiCol_ColumnActive]  = ImVec4(0.00f,
    // 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]    = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
    style.Colors[ImGuiCol_ResizeGripHovered] =
        ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
    style.Colors[ImGuiCol_ResizeGripActive] =
        ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    // style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.78f, 0.78f, 0.35f);
    // style.Colors[ImGuiCol_CloseButtonHovered] =
    ImVec4(0.00f, 0.78f, 0.78f, 0.47f);
    // style.Colors[ImGuiCol_CloseButtonActive] =
    ImVec4(0.00f, 0.78f, 0.78f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] =
        ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] =
        ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);
    // style.Colors[ImGuiCol_TooltipBg]      = ImVec4(0.00f, 0.13f, 0.13f,
    // 0.90f); style.Colors[ImGuiCol_ModalWindowDarkening] =
    ImVec4(0.04f, 0.10f, 0.09f, 0.51f);
}
