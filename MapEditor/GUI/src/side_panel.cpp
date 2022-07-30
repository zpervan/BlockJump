#include "side_panel.h"

#include "MapEditor/Core/src/bootstrap.h"

SidePanel::SidePanel(MapEditorEventSystem& map_editor_events_system) : map_editor_events_system_(map_editor_events_system){}

void SidePanel::Show()
{
    ImGui::SetNextWindowPos(Configuration::Side_Bar_Position);
    ImGui::SetNextWindowSize(Configuration::Side_Bar_Size);

    ImGui::Begin("Tiles", nullptr, side_panel_flags_);

    ImGui::Text("Characters");
    ImGui::NewLine();

    ImGui::ImageButton(*AssetsManager::GetPlayerEntity(), {30.0f, 30.0f},10);

    ImGui::NewLine();
    ImGui::Text("Background");
    ImGui::NewLine();

    if(ImGui::ImageButton(*AssetsManager::GetBackgroundDirt(), {30.0f, 30.0f}, 10))
    {
        spdlog::debug("Pressing the background button");
        map_editor_events_system_.Set(MapEditorEvent::Add);
    }

    ImGui::End();
}
