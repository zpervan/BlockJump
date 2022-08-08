#include "dialog_with_path.h"

#include <spdlog/spdlog.h>

#include "MapEditor/Core/src/bootstrap.h"

DialogWithPath::DialogWithPath(MapEditorEventSystem& map_editor_event_system, MapEditorEvent map_editor_event)
    : map_editor_event_system_(map_editor_event_system), path_("...")
{
    file_browser_ = ImGui::FileBrowser(ImGuiFileBrowserFlags_SelectDirectory | ImGuiFileBrowserFlags_CloseOnEsc);
    file_browser_.SetTitle("Select path");
    file_browser_.SetTypeFilters({".map"});
}

void DialogWithPath::Show(const std::string& title, const std::string& message)
{
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    if(!isOpen)
    {
        isOpen = true;
    }

    if (ImGui::Begin(title.c_str(), &isOpen, Configuration::Window_Flags | ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("%s", message.c_str());

        if (ImGui::Button("Select"))
        {
            spdlog::debug("Button for path selection clicked");

            file_browser_.Open();
        }

        ImGui::SameLine();
        ImGui::Text("%s", path_.c_str());

        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            map_editor_event_system_.Set(MapEditorEvent::SavingConfirmed);
            isOpen = false;
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            map_editor_event_system_.Set(MapEditorEvent::None);
            isOpen = false;
        }

        ImGui::End();

        file_browser_.Display();
        if(file_browser_.HasSelected())
        {
            path_ = file_browser_.GetSelected();
            file_browser_.ClearSelected();
        }
    }
}
