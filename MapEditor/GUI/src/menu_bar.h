#ifndef BLOCKJUMP_MENU_BAR_H
#define BLOCKJUMP_MENU_BAR_H

#include "imgui.h"

namespace MenuBar
{

inline void Show()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Application"))
        {
            ImGui::MenuItem("Restart", nullptr);
            ImGui::MenuItem("Quit", nullptr);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Usage", nullptr);
            ImGui::MenuItem("About", nullptr);

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

}  // namespace MenuBar

#endif  // BLOCKJUMP_MENU_BAR_H
