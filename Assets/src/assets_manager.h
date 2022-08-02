#ifndef BLOCKJUMP_ASSETS_MANAGER_H
#define BLOCKJUMP_ASSETS_MANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <memory>

/// @brief Contains all initialization and loading logic for assets used in the simulation.
class AssetsManager
{
  public:
    /// @brief Initializes all asset objects on specified asset textures.
    static void Initialize();

    /// Getters
    static sf::Texture* Player();
    static sf::Texture* DirtWithGrass();
    static sf::Texture* Brick();

  private:
    static std::unique_ptr<sf::Texture> LoadAsset(const std::string& asset_name);

    inline static std::unique_ptr<sf::Texture> player_entity_;
    inline static std::unique_ptr<sf::Texture> background_dirt_with_grass_;
    inline static std::unique_ptr<sf::Texture> background_brick_;
};

#endif  // BLOCKJUMP_ASSETS_MANAGER_H
