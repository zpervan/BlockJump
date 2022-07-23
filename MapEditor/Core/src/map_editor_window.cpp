#include "map_editor_window.h"

#include "MapEditor/bootstrap.h"

#include <imgui-SFML.h>
#include <spdlog/spdlog.h>

MapEditorWindow::MapEditorWindow(std::string title) : delta_clock_(sf::Clock()),window_title_(std::move(title)), is_done_(false)
{
    const auto width = static_cast<unsigned int>(Configuration::Screen_Size.x);
    const auto height = static_cast<unsigned int>(Configuration::Screen_Size.y);

    window_.create({width, height, 32}, window_title_, sf::Style::Default);

    spdlog::debug("Map editor window size: {}x{}", window_.getSize().x, window_.getSize().y);
    spdlog::debug("View threshold x={} y={}", view_threshold_x_, view_threshold_y_);
}

MapEditorWindow::~MapEditorWindow()
{
    window_.close();
    ImGui::SFML::Shutdown();
}

void MapEditorWindow::BeginDraw()
{
    window_.clear(sf::Color::White);
}

void MapEditorWindow::EndDraw()
{
    window_.display();
}

void MapEditorWindow::Update()
{
    while (window_.pollEvent(event_))
    {
        ImGui::SFML::ProcessEvent(window_, event_);

        if (event_.type == sf::Event::Closed)
        {
            is_done_ = true;
        }
    }

    ImGui::SFML::Update(window_, delta_clock_.restart());
}

bool MapEditorWindow::IsDone()
{
    return is_done_;
}

sf::Vector2u MapEditorWindow::GetWindowSize()
{
    return window_.getSize();
}

void MapEditorWindow::Draw(sf::Drawable& drawable)
{
    window_.draw(drawable);
}

void MapEditorWindow::SetView(const sf::View& view)
{
    window_.setView(view);
}

const sf::View& MapEditorWindow::GetView() const
{
    return view_;
}

sf::RenderWindow& MapEditorWindow::Get()
{
    return window_;
}
