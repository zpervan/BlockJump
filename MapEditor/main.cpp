#include <spdlog/spdlog.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "MapEditor/GUI/src/menu_bar.h"
#include "MapEditor/utility.h"
#include "imgui-SFML.h"

int main()
{
    const auto screen_size{Utility::GetDisplaySize()};
    sf::RenderWindow window({screen_size.first, screen_size.second}, "Block Jump - Map Editor");

// Use debug messages in non-optimized (debug) mode
#ifndef __OPTIMIZE__
    spdlog::set_level(spdlog::level::debug);
#endif

    spdlog::debug("Window size {}x{}", window.getSize().x, window.getSize().y);

    (void)ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    sf::CircleShape shape(100.0f, 200);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(screen_size.first / 3.0f, screen_size.second / 3.0f);

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

            window.clear();
            window.draw(shape);
            ImGui::SFML::Render(window);
            window.display();
        }
    }

    ImGui::SFML::Shutdown();

    return EXIT_SUCCESS;
}
