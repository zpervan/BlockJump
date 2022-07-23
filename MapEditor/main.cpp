#include <imgui-SFML.h>
#include <SFML/Graphics/RectangleShape.hpp>

#include "MapEditor/Core/src/map_editor_events.h"
#include "MapEditor/Core/src/map_editor_window.h"
#include "MapEditor/GUI/src/menu_bar.h"
#include "MapEditor/GUI/src/side_panel.h"
#include "MapEditor/bootstrap.h"

int main()
{
    // Initialize static and global data
    Bootstrap::Initialize();

    // Initialize the rendering window and all necessary components
    MapEditorEventSystem map_editor_events_system{};
    MapEditorWindow window{map_editor_events_system, "Block Jump - Map Editor"};
    (void)ImGui::SFML::Init(window.Get());

    // Initialize components - usually that use the map editor event system
    SidePanel side_panel{map_editor_events_system};

    /// @TODO: Move this out once we have the shape creation logic
    sf::RectangleShape shape({50.0f, 50.0f});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(Configuration::Screen_Size.x / 3.0f, Configuration::Screen_Size.y / 3.0f);

    while (!window.IsDone())
    {
        window.Update();

        // GUI components
        MenuBar::Show();
        side_panel.Show();

        window.BeginDraw();

        /// @TODO: Move to a separate class - shape creation class
        if(map_editor_events_system.Poll() == MapEditorEvent::Add)
        {
            shape.setPosition(window.GetMousePosition().x - (shape.getSize().x / 2), window.GetMousePosition().y - (shape.getSize().y / 2));
        }

        /// @TODO: Store shapes into a list, then draw
        window.Draw(shape);
        ImGui::SFML::Render(window.Get());
        window.EndDraw();
    }

    return EXIT_SUCCESS;
}
