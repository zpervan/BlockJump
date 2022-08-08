#include "menu_bar.h"

#include <imgui.h>
#include <spdlog/spdlog.h>

#include "MapEditor/GUI/src/dialog_with_path.h"

MenuBar::MenuBar(MapEditorWindow& map_editor_window,
                 TilesService& tiles_service,
                 MapEditorEventSystem& map_editor_event_system)
    : map_editor_window_(map_editor_window),
      map_editor_event_system_(map_editor_event_system)
{
}

void MenuBar::Show()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                spdlog::info("Saving map...");
                map_editor_event_system_.Set(MapEditorEvent::Saving);
            }

            ImGui::MenuItem("Load", nullptr);

            ImGui::EndMenu();
        }

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
