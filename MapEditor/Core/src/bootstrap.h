#ifndef BLOCKJUMP_BOOTSTRAP_H
#define BLOCKJUMP_BOOTSTRAP_H

#include "imgui.h"

/// @TODO: Extract into a configurations file
namespace Configuration
{
// Window
inline ImVec2 Screen_Size;

// GUI components
inline ImVec2 Side_Bar_Size;
inline ImVec2 Side_Bar_Position;
inline ImVec2 Button_Size;
inline ImGuiWindowFlags Window_Flags {ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoMove |
                                     ImGuiWindowFlags_NoResize};

// Tiles
inline constexpr float Tile_Size{50.0f};
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
