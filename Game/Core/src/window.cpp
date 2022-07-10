#include "Game/Core/src/window.h"

#include <SFML/Window/Event.hpp>
#include <utility>

Window::Window(std::string title, const sf::Vector2u& size)
    : window_size_(size), window_title_(std::move(title)), is_done_(false)
{
    window_.create({window_size_.x, window_size_.y, 32}, window_title_, sf::Style::Default);
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
    sf::Event event{};
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
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
