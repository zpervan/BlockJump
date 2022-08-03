#include "menu_bar.h"

#include <imgui.h>
#include <spdlog/spdlog.h>

#include "MapEditor/Map/src/map_serialization.h"

MenuBar::MenuBar(MapEditorWindow& map_editor_window, TilesService& tiles_service)
    : map_editor_window_(map_editor_window), tiles_service_(tiles_service)
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
                MapSerialization::Serialize(tiles_service_.GetTiles());
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
