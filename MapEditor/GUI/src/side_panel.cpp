#include "side_panel.h"

#include "MapEditor/Core/src/bootstrap.h"

SidePanel::SidePanel(TilesService& tiles_service) : tiles_service_(tiles_service)
{
}

void SidePanel::Show()
{
    ImGui::SetNextWindowPos(Configuration::Side_Bar_Position);
    ImGui::SetNextWindowSize(Configuration::Side_Bar_Size);

    ImGui::Begin("Tiles", nullptr, Configuration::Window_Flags);

    ImGui::Text("Characters");
    ImGui::NewLine();

    if (ImGui::ImageButton(*AssetsManager::Get(AssetType::Player), {Configuration::Button_Size.x, Configuration::Button_Size.y}, padding_))
    {
        spdlog::debug("Pressed characters \"Player\" button");
        tiles_service_.BeginPlacement(AssetType::Player);
    }

    ImGui::NewLine();
    ImGui::Text("Background");
    ImGui::NewLine();

    /// @TODO: Automatically add buttons by detecting the number of assets
    if (ImGui::ImageButton(*AssetsManager::Get(AssetType::DirtWithGrass), {Configuration::Button_Size.x, Configuration::Button_Size.y}, padding_))
    {
        spdlog::debug("Pressed background \"DirtWithGrass\" button");
        tiles_service_.BeginPlacement(AssetType::DirtWithGrass);
    }

    ImGui::SameLine();

    if (ImGui::ImageButton(*AssetsManager::Get(AssetType::Brick), {Configuration::Button_Size.x, Configuration::Button_Size.y}, padding_))
    {
        spdlog::debug("Pressed background \"Brick\" button");
        tiles_service_.BeginPlacement(AssetType::Brick);
    }

    ImGui::End();
}
