#ifndef BLOCKJUMP_METADATA_H
#define BLOCKJUMP_METADATA_H

#include <string>

#include "Library/src/paths.h"

/// @brief Contains all game and player information which is fetched from various parts of the game.
class Metadata
{
  public:
    std::string PlayingMapPath() { return playing_map_path_; }
    void SetPlayingMapPath(const std::string& map_path) { playing_map_path_ = map_path; }

    std::string PlayerName() const { return player_name_; }
    void SetPlayerName(const std::string& player_name) { player_name_ = player_name; }

  private:
    /// @TODO: This is currently a default value as the start game menu is not implemented. Remove it once it's done.
    std::string playing_map_path_{Paths::MapsDirectoryPath() + "single_player_test.map"};
    std::string player_name_;
};

#endif  // BLOCKJUMP_METADATA_H
