#ifndef BLOCKJUMP_GRID_H
#define BLOCKJUMP_GRID_H

#include "MapEditor/Core/src/map_editor_window.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Grid
{
  public:
    void Create(sf::Vector2i grid_size);
    const std::vector<sf::RectangleShape*>& GetGridShapes() const;

  private:
    sf::Vector2f CalculateShapePosition(std::size_t row, std::size_t column) const;

    std::vector<sf::RectangleShape*> grid_shapes_;
    sf::Vector2i grid_size_;
    sf::Vector2f grid_center_position_;
    float grid_left_start_position_;
    float grid_upper_start_position_;
};

#endif  // BLOCKJUMP_GRID_H
