#ifndef BLOCKJUMP_GAME_WINDOW_H
#define BLOCKJUMP_GAME_WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class GameWindow
{
  public:
    GameWindow(std::string title);
    ~GameWindow();

    void BeginDraw();
    void EndDraw();
    void Update();
    void Draw(sf::Drawable& drawable);
    void UpdatePlayerView(const sf::Vector2f& player_position);
    bool IsDone();

    sf::Vector2u GetWindowSize();
    void SetView(const sf::View& view);
    const sf::View& GetView() const;

  private:
    sf::Event event_;
    sf::RenderWindow window_;
    sf::View view_;

  private:
    std::string window_title_;
    float view_threshold_x_;
    float view_threshold_y_;
    bool is_done_;
};

#endif  // BLOCKJUMP_GAME_WINDOW_H
