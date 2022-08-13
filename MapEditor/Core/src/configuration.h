#ifndef BLOCKJUMP_CONFIGURATION_H
#define BLOCKJUMP_CONFIGURATION_H

#include <string>
#include <imgui.h>

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

// Map
static char Map_Name[64]{"example.map"};
}

#endif  // BLOCKJUMP_CONFIGURATION_H
