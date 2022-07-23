#ifndef BLOCKJUMP_MAP_EDITOR_WINDOW_H
#define BLOCKJUMP_MAP_EDITOR_WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "MapEditor/Core/src/map_editor_events.h"

class MapEditorWindow
{
  public:
    MapEditorWindow(MapEditorEventSystem& map_editor_event_system, std::string title);
    ~MapEditorWindow();

    void BeginDraw();
    void EndDraw();
    void Update();
    void Draw(sf::Drawable& drawable);
    bool IsDone();

    sf::Vector2u GetWindowSize();
    void SetView(const sf::View& view);
    const sf::View& GetView() const;
    sf::RenderWindow& Get();
    const sf::Vector2i& GetMousePosition() const;

  private:
    MapEditorEventSystem& map_editor_event_system_;
    sf::Clock delta_clock_;
    sf::Event event_;
    sf::RenderWindow window_;
    sf::View view_;

    sf::Vector2i mouse_position_;
    std::string window_title_;
    float view_threshold_x_;
    float view_threshold_y_;
    bool is_done_;
};

#endif  // BLOCKJUMP_MAP_EDITOR_WINDOW_H
