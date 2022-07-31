#ifndef BLOCKJUMP_BOOTSTRAP_H
#define BLOCKJUMP_BOOTSTRAP_H

#include "imgui.h"

namespace Configuration
{
// Window
inline ImVec2 Screen_Size;

// GUI components
inline ImVec2 Side_Bar_Size;
inline ImVec2 Side_Bar_Position;

// Tiles
inline constexpr float tile_size{50.0f};
}

class Bootstrap
{
  public:
    /// @brief Initialize all configuration parameters for the application.
    static void Initialize();

  private:
    static ImVec2 ScreenSize();
};

#endif  // BLOCKJUMP_BOOTSTRAP_H
