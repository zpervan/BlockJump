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

    /// @brief Prepares the environment for a new drawing process.
    void BeginDraw();

    /// @brief Shows all drawable elements.
    void EndDraw();

    /// @brief Polls all events from the application and updates the application state afterwards.
    void Update();

    /// @brief Draws an object to the rendering window.
    /// @param drawable Object to be drawn
    void Draw(sf::Drawable& drawable);

    /// @brief Fetches the render window of the current application session.
    /// @return Rendering window
    sf::RenderWindow& Get();

    /// Getters and setters
    bool IsDone();
    void SetIsDone(bool is_done);

    const sf::View& GetView() const;
    void SetView(const sf::View& view);

    sf::Vector2u GetWindowSize();
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
