#include "MapEditor/Core/src/bootstrap.h"

#include "Assets/src/assets_manager.h"

#include <spdlog/spdlog.h>

/// @TODO: Add Windows option
#ifdef __linux__
#include <X11/Xlib.h>
#endif

void Bootstrap::Initialize()
{
    spdlog::info("Initializing...");
#ifndef __OPTIMIZE__
    // Use debug messages in non-optimized (debug) mode
    spdlog::set_level(spdlog::level::debug);
#endif
    Configuration::Screen_Size = Bootstrap::ScreenSize();
    AssetsManager::Initialize();
}

/// @TODO: Consider how to handle multi-screen size
ImVec2 Bootstrap::ScreenSize()
{
    ImVec2 window_size{0.0f, 0.0f};

#ifdef __linux__
    Display* display{XOpenDisplay(nullptr)};
    Screen* screen{DefaultScreenOfDisplay(display)};

    window_size.x = static_cast<float>(screen->width);
    window_size.y = static_cast<float>(screen->height);
#endif

    return window_size;
}
