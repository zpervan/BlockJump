#ifndef BLOCKJUMP_DIALOG_WITH_PATH_H
#define BLOCKJUMP_DIALOG_WITH_PATH_H

#include <imgui.h>
#include <imfilebrowser.h>
#include <string>

#include "MapEditor/Core/src/map_editor_events.h"

class DialogWithPath
{
  public:
    DialogWithPath(MapEditorEventSystem& map_editor_event_system, MapEditorEvent map_editor_event);

    void Show(const std::string& title, const std::string& message);

  private:
    MapEditorEventSystem& map_editor_event_system_;
    ImGui::FileBrowser file_browser_;
    std::string path_;
    bool isOpen{false};
};

#endif