#ifndef BLOCKJUMP_WINDOW_H
#define BLOCKJUMP_WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>

class Window
{
  public:
    Window(std::string title, const sf::Vector2u& size);
    ~Window();

    void BeginDraw();
    void EndDraw();
    void Update();
    void Draw(sf::Drawable& drawable);

    bool IsDone();
    sf::Vector2u GetWindowSize();

  private:
    sf::RenderWindow window_;
    sf::Vector2u window_size_;
    std::string window_title_;
    bool is_done_;
};

#endif  // BLOCKJUMP_WINDOW_H
