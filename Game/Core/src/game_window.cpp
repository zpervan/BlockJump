#include "Game/Core/src/game_window.h"

#include <spdlog/spdlog.h>

#include <utility>

#include "Game/constants.h"

/// @TODO: Add Windows option
#ifdef __linux__
#include <X11/Xlib.h>

#include <valarray>
#endif

namespace
{

inline std::pair<std::uint32_t , std::uint32_t> GetDisplaySize()
{
    std::pair<std::uint32_t , std::uint32_t> window_size{0, 0};

#ifdef __linux__
    Display* display{XOpenDisplay(nullptr)};
    Screen* screen{DefaultScreenOfDisplay(display)};

    window_size.first = screen->width;
    window_size.second = screen->height;
#endif

    return window_size;
}

}

GameWindow::GameWindow(std::string title) :
      window_title_(std::move(title)),
      is_done_(false)
{
    const auto display_size{GetDisplaySize()};
    window_.create({display_size.first, display_size.second, 32}, window_title_, sf::Style::Default);
    view_threshold_x_ = view_.getSize().x * 0.2f;
    view_threshold_y_ = view_.getSize().y * 0.2f;

    spdlog::debug("Game window size: {}x{}", window_.getSize().x, window_.getSize().y);
    spdlog::debug("View threshold x={} y={}", view_threshold_x_, view_threshold_y_);
}

GameWindow::~GameWindow()
{
    window_.close();
}

void GameWindow::BeginDraw()
{
    window_.clear(sf::Color::White);
}

void GameWindow::EndDraw()
{
    window_.display();
}

void GameWindow::Update()
{
    while (window_.pollEvent(event_))
    {
        if (event_.type == sf::Event::Closed)
        {
            is_done_ = true;
        }
    }
}

bool GameWindow::IsDone()
{
    return is_done_;
}

sf::Vector2u GameWindow::GetWindowSize()
{
    return window_.getSize();
}

void GameWindow::Draw(sf::Drawable& drawable)
{
    window_.draw(drawable);
}

void GameWindow::SetView(const sf::View& view)
{
    window_.setView(view);
}

const sf::View& GameWindow::GetView() const
{
    return view_;
}

void GameWindow::UpdatePlayerView(const sf::Vector2f& player_position)
{
    sf::Vector2f offset{0.0f, 0.0f};

    // If the positive player position x is larger than the positive threshold view x
    if(player_position.x > (view_.getCenter().x + view_threshold_x_))
    {
        offset.x += Constants::MOVEMENT_OFFSET;
    }

    // If the negative player position x is larger than the negative threshold view x
    if(player_position.x < (view_.getCenter().x - view_threshold_x_))
    {
        offset.x -= Constants::MOVEMENT_OFFSET;
    }

    // If the negative player position y is larger than the negative threshold view y
    if(player_position.y > (view_.getCenter().y + view_threshold_y_))
    {
        offset.y += Constants::MOVEMENT_OFFSET;
    }

    // If the negative player position y is larger than the negative threshold view y
    if(player_position.y < (view_.getCenter().y - view_threshold_y_))
    {
        offset.y -= Constants::MOVEMENT_OFFSET;
    }

    if((offset.x != 0.0f) || (offset.y != 0.0f))
    {
        view_.move(offset);
        SetView(view_);
    }
}
