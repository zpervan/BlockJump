#include "dialog_with_path.h"

#include <spdlog/spdlog.h>

#include "MapEditor/Core/src/configuration.h"
#include "MapEditor/GUI/src/button.h"

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

    if(!is_open_)
    {
        is_open_ = true;
    }

    if (ImGui::Begin(title.c_str(), &is_open_, Configuration::Window_Flags | ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("%s", message.c_str());

        if (ImGui::Button("Select"))
        {
            spdlog::debug("Button for path selection clicked");

            file_browser_.Open();
        }

        ImGui::SameLine();
        ImGui::Text("%s", path_.c_str());

        ImGui::Checkbox("Remember location?", &remember_location_);

        ImGui::Text("Map name:"); ImGui::SameLine();

        ImGui::InputText("##MapName", Configuration::Map_Name, IM_ARRAYSIZE(Configuration::Map_Name));

        ImGui::Separator();

        auto savingConfirmedCallback = [this]() {
            map_editor_event_system_.Set(MapEditorEvent::SavingConfirmed);
            is_open_ = false;
        };

        Button::Show("OK", savingConfirmedCallback, !std::filesystem::exists(path_));

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        auto savingCanceledCallback = [this]() {
            map_editor_event_system_.Set(MapEditorEvent::None);
            is_open_ = false;
        };

        Button::Show("Cancel", savingCanceledCallback);

        ImGui::End();

        file_browser_.Display();
        if(file_browser_.HasSelected())
        {
            path_ = file_browser_.GetSelected();
            file_browser_.ClearSelected();
        }
    }
}
