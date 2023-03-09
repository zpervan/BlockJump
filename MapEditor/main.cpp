#include <imgui-SFML.h>

#include <future>

#include "MapEditor/Core/src/bootstrap.h"
#include "MapEditor/Core/src/map_editor_events.h"
#include "MapEditor/Core/src/map_editor_window.h"
#include "MapEditor/GUI/src/dialog_with_path.h"
#include "MapEditor/GUI/src/menu_bar.h"
#include "MapEditor/GUI/src/side_panel.h"
#include "MapEditor/Map/src/grid.h"
#include "MapEditor/Map/src/tiles_service.h"
#include "Library/src/map_manager.h"

int main()
{
    // Initialize static and global data
    Bootstrap::Initialize();

    // Initialize the rendering window and all necessary components
    MapEditorEventSystem map_editor_event_system{};
    MapEditorWindow window{map_editor_event_system, "Block Jump - Map Editor"};
    (void)ImGui::SFML::Init(window.Get());

    // Initialize map creation functionality
    Grid grid;
    grid.Create({30,18});
    TilesService tiles_service{map_editor_event_system};
    std::future<bool> serialization_result;

    /// @TODO: Consider to have some kind of dependency injection to avoid passing single objects to components
    // Initialize GUI components
    SidePanel side_panel{tiles_service};
    MenuBar menu_bar{window, tiles_service, map_editor_event_system};
    DialogWithPath save_dialog{map_editor_event_system, MapEditorEvent::SavingConfirmed};
    DialogWithPath load_dialog{map_editor_event_system, MapEditorEvent::LoadingConfirmed};

    while (!window.IsDone())
    {
        window.Update();

        // GUI components
        menu_bar.Show();
        side_panel.Show();

        window.BeginDraw();

        if (tiles_service.GetTemporaryTile())
        {
            switch (map_editor_event_system.Poll())
            {
                case MapEditorEvent::None:
                    tiles_service.DeleteTemporaryTile();
                    break;

                case MapEditorEvent::Add:
                    for (auto& e : grid.GetGridShapes())
                    {
                        if (e->getGlobalBounds().contains(window.GetMousePosition().x, window.GetMousePosition().y))
                        {
                            tiles_service.GetTemporaryTile()->first.setPosition(e->getPosition());
                        }
                    }
                    window.Draw(tiles_service.GetTemporaryTile()->first);
                    break;

                // Multitile placement
                case MapEditorEvent::Set:
                    auto asset_type = tiles_service.GetTemporaryTile()->second;
                    tiles_service.FinishPlacement();
                    map_editor_event_system.Set(MapEditorEvent::Add);
                    tiles_service.BeginPlacement(asset_type);
                    break;
            }
        }

        if (map_editor_event_system.Poll() == MapEditorEvent::Saving)
        {
            save_dialog.Show("Save", "Please select a path to save your map.");
        }

        if (map_editor_event_system.Poll() == MapEditorEvent::SavingConfirmed)
        {
            if (!serialization_result.valid())
            {
                spdlog::debug("Calling serialization thread...");
                serialization_result = std::async(std::launch::async, &MapManager::Save, tiles_service.CloneTiles());
            }

            if (serialization_result.valid())
            {
                spdlog::debug("Finished with serialization thread.");
                map_editor_event_system.Set(MapEditorEvent::None);
            }
        }

        if (map_editor_event_system.Poll() == MapEditorEvent::Loading)
        {
            load_dialog.Show("Load map", "Please select a map to load.");
        }

        if (map_editor_event_system.Poll() == MapEditorEvent::LoadingConfirmed)
        {
            spdlog::debug("TODO: Implement loading functionality");
        }

        // Draw all placed tiles
        for (const auto& tile : tiles_service.GetTiles())
        {
            if (!tile)
            {
                continue;
            }

            window.Draw(tile->first);
        }

        for (const auto& grid_line : grid.GetGridShapes())
        {
            window.Draw(*grid_line);
        }

        ImGui::SFML::Render(window.Get());
        window.EndDraw();
    }

    return EXIT_SUCCESS;
}
