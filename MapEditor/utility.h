#ifndef BLOCKJUMP_UTILITY_H
#define BLOCKJUMP_UTILITY_H

#include <utility>

/// @TODO: Add Windows option
#ifdef __linux__
#include <X11/Xlib.h>
#endif

namespace Utility
{

inline std::pair<std::uint32_t , std::uint32_t> GetDisplaySize()
{
    std::pair<std::uint32_t , std::uint32_t> window_size{0, 0};

#ifdef __linux__
    Display* display{XOpenDisplay(nullptr)};
    Screen* screen{DefaultScreenOfDisplay(display)};

    window_size.first = screen->width;
    window_size.second = screen->height;
#endif

    return window_size;
}

}  // namespace Utility

#endif  // BLOCKJUMP_UTILITY_H
