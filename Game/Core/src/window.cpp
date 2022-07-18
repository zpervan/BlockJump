#include "Game/Core/src/window.h"
#include "Game/constants.h"

#include <spdlog/spdlog.h>
#include <utility>

Window::Window(std::string title, const sf::Vector2u& size)
    : window_size_(size),
      window_title_(std::move(title)),
      is_done_(false)
{
    window_.create({window_size_.x, window_size_.y, 32}, window_title_, sf::Style::Default);
    view_threshold_x_ = view_.getSize().x * 0.2f;
    view_threshold_y_ = view_.getSize().y * 0.2f;
}

Window::~Window()
{
    window_.close();
}

void Window::BeginDraw()
{
    window_.clear(sf::Color::White);
}

void Window::EndDraw()
{
    window_.display();
}

void Window::Update()
{
    while (window_.pollEvent(event_))
    {
        if (event_.type == sf::Event::Closed)
        {
            is_done_ = true;
        }
    }
}

bool Window::IsDone()
{
    return is_done_;
}

sf::Vector2u Window::GetWindowSize()
{
    return window_size_;
}

void Window::Draw(sf::Drawable& drawable)
{
    window_.draw(drawable);
}

void Window::SetView(const sf::View& view)
{
    window_.setView(view);
}

const sf::View& Window::GetView() const
{
    return view_;
}

void Window::UpdatePlayerView(const sf::Vector2f& player_position)
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
