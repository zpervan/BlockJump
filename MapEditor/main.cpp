#include <imgui-SFML.h>
#include <SFML/Graphics/RectangleShape.hpp>

#include "MapEditor/Core/src/bootstrap.h"
#include "MapEditor/Core/src/map_editor_events.h"
#include "MapEditor/Core/src/map_editor_window.h"
#include "MapEditor/GUI/src/menu_bar.h"
#include "MapEditor/GUI/src/side_panel.h"
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
            auto* temporary_tile{tiles.GetTemporaryTile()};
            temporary_tile->setPosition(window.GetMousePosition().x - (temporary_tile->getSize().x / 2), window.GetMousePosition().y - (temporary_tile->getSize().y / 2));
            window.Draw(temporary_tile);
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

        ImGui::SFML::Render(window.Get());
        window.EndDraw();
    }

    return EXIT_SUCCESS;
}
