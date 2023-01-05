#ifndef BLOCKJUMP_ASSETS_MANAGER_H
#define BLOCKJUMP_ASSETS_MANAGER_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

/// @brief Used to define the asset type. Must be aligned with the enum in Map.proto
enum class AssetType
{
    None = 0,
    Player,
    DirtWithGrass,
    Brick
};

/// @brief Used to select which type of font to fetch
enum class FontType
{
    Header = 0,
    Button
};

/// @brief Contains all initialization and loading logic for assets used in the simulation.
class AssetsManager
{
  public:
    /// @brief Initializes all asset objects on specified asset textures.
    static void Initialize();

    /// Getters
    static sf::Texture* GetTexture(AssetType type);
    static sf::Font* GetFont(FontType font);

  private:
    static std::unique_ptr<sf::Texture> LoadAsset(const std::string& asset_name);
    static std::unique_ptr<sf::Font> LoadFont(const std::string& font_name);

    inline static std::unique_ptr<sf::Texture> player_entity_;
    inline static std::unique_ptr<sf::Texture> background_dirt_with_grass_;
    inline static std::unique_ptr<sf::Texture> background_brick_;
    inline static std::unique_ptr<sf::Font> button_font_;
    inline static std::unique_ptr<sf::Font> header_font_;
};

#endif  // BLOCKJUMP_ASSETS_MANAGER_H
