#include "MapEditor/Core/src/bootstrap.h"

#include <spdlog/spdlog.h>

#include "Assets/src/assets_manager.h"
#include "MapEditor/Core/src/configuration.h"

#include <GLFW/glfw3.h>

void Bootstrap::Initialize()
{
    spdlog::info("Initializing...");
#ifndef __OPTIMIZE__
    // Use debug messages in non-optimized (debug) mode
    spdlog::set_level(spdlog::level::debug);
#endif
    Configuration::Screen_Size = Bootstrap::ScreenSize();
    Configuration::Side_Bar_Position = ImVec2(0, 18);
    Configuration::Side_Bar_Size = ImVec2(Configuration::Screen_Size.x * 0.2f, Configuration::Screen_Size.y);
    Configuration::Button_Size = ImVec2(30.0f, 30.0f);

    AssetsManager::Initialize();
}

ImVec2 Bootstrap::ScreenSize()
{
    ImVec2 window_size{0, 0};
    glfwInit();
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    window_size.x = mode->width;
    /// @TODO: Subtract the OS menu bar height to get the actual application height
    window_size.y = mode->height - 100.0f;

    return window_size;
}
