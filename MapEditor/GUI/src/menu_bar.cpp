#include "menu_bar.h"

#include <imgui.h>

MenuBar::MenuBar(MapEditorWindow& map_editor_window) : map_editor_window_(map_editor_window){}

void MenuBar::Show()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Application"))
        {
            ImGui::MenuItem("Restart", nullptr);

            if (ImGui::MenuItem("Quit", nullptr))
            {
                map_editor_window_.SetIsDone(true);
            };

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
