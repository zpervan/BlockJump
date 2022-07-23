#ifndef BLOCKJUMP_SIDE_PANEL_H
#define BLOCKJUMP_SIDE_PANEL_H

#include <imgui.h>
#include <spdlog/spdlog.h>

#include "Assets/src/assets_manager.h"
#include "MapEditor/Core/src/map_editor_events.h"
#include "imgui-SFML.h"

namespace
{
    ImGuiWindowFlags side_panel_flags_ {ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing};
}

class SidePanel
{
  public:
    SidePanel(MapEditorEventSystem& map_editor_events_system);
    void Show();

  private:
    MapEditorEventSystem& map_editor_events_system_;
};

#endif  // BLOCKJUMP_SIDE_PANEL_H
