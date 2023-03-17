#include "grid.h"

#include "Library/src/tiles.h"
#include "MapEditor/Core/src/configuration.h"

static const float outline_thickness{1.0f};
static const float cell_size{DEFAULT_TILE_SIZE.x - outline_thickness};

void Grid::Create(sf::Vector2i grid_size)
{
    grid_size_ = grid_size;
    grid_shapes_.reserve(grid_size_.x * grid_size_.y);

    // Divide the width center of the screen without the sidebar width size, then add this value again in order to
    // place the grid at the exact center of the edit viewport
    grid_center_position_.x = ((Configuration::Screen_Size.x - Configuration::Side_Bar_Size.x) / 2) + Configuration::Side_Bar_Size.x;
    grid_center_position_.y = Configuration::Screen_Size.y / 2;

    grid_left_start_position_ = grid_center_position_.x - ((grid_size_.x / 2.0f) * DEFAULT_TILE_SIZE.x);
    grid_upper_start_position_ = grid_center_position_.y - ((grid_size_.y / 2.0f) * DEFAULT_TILE_SIZE.y);

    const sf::Color cell_color{255, 51, 0, 10};
    const sf::Color outline_color{0, 191, 54};

    for (std::size_t row_index{0}; row_index < grid_size_.y; ++row_index)
    {
        for (std::size_t column_index{0}; column_index < grid_size_.x; ++column_index)
        {
            auto* shape = new sf::RectangleShape({cell_size, cell_size});
            shape->setPosition(CalculateShapePosition(row_index, column_index));
            shape->setFillColor(cell_color);
            shape->setOutlineColor(outline_color);
            shape->setOutlineThickness(outline_thickness);

            grid_shapes_.emplace_back(shape);
        }
    }
}

const std::vector<sf::RectangleShape*>& Grid::GetGridShapes() const
{
    return grid_shapes_;
}

sf::Vector2f Grid::CalculateShapePosition(std::size_t row, std::size_t column) const
{
    const float cell_x_position = grid_left_start_position_ + (DEFAULT_TILE_SIZE.x * column);
    const float cell_y_position = grid_upper_start_position_ + (DEFAULT_TILE_SIZE.y * row);

    return {cell_x_position, cell_y_position};
}
