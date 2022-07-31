#include <imgui-SFML.h>
#include <SFML/Graphics/RectangleShape.hpp>

#include "MapEditor/Core/src/bootstrap.h"
#include "MapEditor/Core/src/map_editor_events.h"
#include "MapEditor/Core/src/map_editor_window.h"
#include "MapEditor/GUI/src/menu_bar.h"
#include "MapEditor/GUI/src/side_panel.h"
#include "MapEditor/Map/src/grid.h"
#include "MapEditor/Map/src/tiles.h"

int main()
{
    // Initialize static and global data
    Bootstrap::Initialize();

    // Initialize the rendering window and all necessary components
    MapEditorEventSystem map_editor_events_system{};
    MapEditorWindow window{map_editor_events_system, "Block Jump - Map Editor"};
    (void)ImGui::SFML::Init(window.Get());

    /// @TODO: Consider to have some kind of dependency injection to avoid passing single objects to components
    // Initialize components - usually that use the map editor event system
    SidePanel side_panel{map_editor_events_system};
    MenuBar menu_bar{window};

    // Initialize map creation functionality
    Grid grid;
    grid.Create({30,18});
    Tiles tiles{map_editor_events_system};

    while (!window.IsDone())
    {
        window.Update();

        // GUI components
        menu_bar.Show();
        side_panel.Show();

        window.BeginDraw();

        if(map_editor_events_system.Poll() == MapEditorEvent::Add)
        {
            tiles.BeginPlacement();

            for (auto & e : grid.GetGridShapes())
            {
                if(e->getGlobalBounds().contains(window.GetMousePosition().x, window.GetMousePosition().y))
                {
                    tiles.GetTemporaryTile()->setPosition(e->getPosition());
                }
            }
            window.Draw(tiles.GetTemporaryTile());
        }

        if(map_editor_events_system.Poll() == MapEditorEvent::None)
        {
            if(tiles.GetTemporaryTile())
            {
                tiles.FinishPlacement();
            }
        }

        // Draw all placed tiles
        for (const auto & tile : tiles.GetTiles())
        {
            window.Draw(tile);
        }

        for (const auto & grid_line : grid.GetGridShapes())
        {
            window.Draw(grid_line);
        }

        ImGui::SFML::Render(window.Get());
        window.EndDraw();
    }

    return EXIT_SUCCESS;
}
