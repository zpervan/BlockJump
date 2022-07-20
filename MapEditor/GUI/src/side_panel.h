#ifndef BLOCKJUMP_SIDE_PANEL_H
#define BLOCKJUMP_SIDE_PANEL_H

#include "MapEditor/bootstrap.h"
#include "Assets/src/assets_manager.h"

#include "imgui-SFML.h"

namespace
{
    ImGuiWindowFlags side_panel_flags_ {ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing};
}

namespace SidePanel
{

inline void Show()
{
    ImGui::SetNextWindowPos({0,20});
    ImGui::SetNextWindowSize({Configuration::Screen_Size.x * 0.1f, Configuration::Screen_Size.y});

    ImGui::Begin("Tiles", nullptr, side_panel_flags_);

    ImGui::Text("Characters");
    ImGui::NewLine();

    ImGui::PushID(0);
    ImGui::ImageButton(*AssetsManager::GetPlayerEntity(), {30.0f, 30.0f},10);
    ImGui::PopID();

    ImGui::NewLine();
    ImGui::Text("Background");
    ImGui::NewLine();

    ImGui::PushID(0);
    ImGui::ImageButton(*AssetsManager::GetBackgroundDirt(), {30.0f, 30.0f}, 10);
    ImGui::PopID();

    ImGui::End();
}

}  // namespace SidePanel

#endif  // BLOCKJUMP_SIDE_PANEL_H
