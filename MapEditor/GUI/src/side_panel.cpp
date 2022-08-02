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

    ImGui::ImageButton(*AssetsManager::Player(), {Configuration::Button_Size.x, Configuration::Button_Size.y}, 10);

    ImGui::NewLine();
    ImGui::Text("Background");
    ImGui::NewLine();

    /// @TODO: Automatically add buttons by detecting the number of assets
    if(ImGui::ImageButton(*AssetsManager::DirtWithGrass(), {Configuration::Button_Size.x, Configuration::Button_Size.y}, 10))
    {
        spdlog::debug("Pressed background \"DirtWithGrass\" button");
        map_editor_events_system_.Set(MapEditorEvent::Add);
    }

    ImGui::SameLine();

    if(ImGui::ImageButton(*AssetsManager::Brick(), {Configuration::Button_Size.x, Configuration::Button_Size.y}, 10))
    {
        spdlog::debug("Pressed background \"Brick\" button");
        map_editor_events_system_.Set(MapEditorEvent::Add);
    }

    ImGui::End();
}
