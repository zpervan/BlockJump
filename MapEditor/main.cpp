#include <spdlog/spdlog.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Assets/src/assets_manager.h"
#include "MapEditor/GUI/src/menu_bar.h"
#include "MapEditor/GUI/src/side_panel.h"
#include "MapEditor/bootstrap.h"
#include "imgui-SFML.h"

int main()
{
    Bootstrap::Initialize();

    // Needed for SFML as the screen size is of type int
    const auto width = static_cast<unsigned int>(Configuration::Screen_Size.x);
    const auto height = static_cast<unsigned int>(Configuration::Screen_Size.y);

    sf::RenderWindow window({width, height}, "Block Jump - Map Editor");
    spdlog::debug("Window size {}x{}", window.getSize().x, window.getSize().y);

    (void)ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    sf::CircleShape shape(100.0f, 200);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(Configuration::Screen_Size.x / 3.0f, Configuration::Screen_Size.y / 3.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            ImGui::SFML::Update(window, deltaClock.restart());

            MenuBar::Show();
            SidePanel::Show();

            window.clear();
            window.draw(shape);
            ImGui::SFML::Render(window);
            window.display();
        }
    }

    ImGui::SFML::Shutdown();

    return EXIT_SUCCESS;
}
