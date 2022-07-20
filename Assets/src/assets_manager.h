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
    static const sf::Texture* GetPlayerEntity();
    static const sf::Texture* GetBackgroundDirt();

  private:
    static std::unique_ptr<sf::Texture> LoadAsset(const std::string& asset_name);

    inline static std::unique_ptr<sf::Texture> player_entity_;
    inline static std::unique_ptr<sf::Texture> background_dirt_;
};

#endif  // BLOCKJUMP_ASSETS_MANAGER_H
