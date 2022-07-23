#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Assets/src/assets_manager.h"
#include "MapEditor/Core/src/map_editor_window.h"
#include "MapEditor/GUI/src/menu_bar.h"
#include "MapEditor/GUI/src/side_panel.h"
#include "MapEditor/bootstrap.h"

#include <imgui-SFML.h>

int main()
{
    Bootstrap::Initialize();

    MapEditorWindow window{"Block Jump - Map Editor"};

    (void)ImGui::SFML::Init(window.Get());

    sf::CircleShape shape(100.0f, 200);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(Configuration::Screen_Size.x / 3.0f, Configuration::Screen_Size.y / 3.0f);

    while (!window.IsDone())
    {
        window.Update();

        // GUI components
        MenuBar::Show();
        SidePanel::Show();

        window.BeginDraw();
        /// @TODO: Store shapes into a list, then draw
        window.Draw(shape);
        ImGui::SFML::Render(window.Get());
        window.EndDraw();
    }

    return EXIT_SUCCESS;
}
