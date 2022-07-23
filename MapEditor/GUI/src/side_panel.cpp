#include "side_panel.h"

#include "MapEditor/bootstrap.h"

SidePanel::SidePanel(MapEditorEventSystem& map_editor_events_system) : map_editor_events_system_(map_editor_events_system){}

void SidePanel::Show()
{
    ImGui::SetNextWindowPos({0,20});
    ImGui::SetNextWindowSize({Configuration::Screen_Size.x * 0.1f, Configuration::Screen_Size.y});

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
