#ifndef BLOCKJUMP_PATHS_H
#define BLOCKJUMP_PATHS_H

#include <spdlog/spdlog.h>

#include <filesystem>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <linux/limits.h>
#include <unistd.h>
#endif

namespace
{
#ifdef WIN32
constexpr auto SPRITES_DIRECTORY{"\\Assets\\Sprites\\"};
constexpr auto MAPS_DIRECTORY{"\\Assets\\Maps\\"};
constexpr auto FONTS_DIRECTORY{"\\Assets\\Fonts\\"};
constexpr auto SOUNDS_DIRECTORY{"\\Assets\\Sounds\\"};
#else
constexpr auto SPRITES_DIRECTORY{"/Assets/Sprites/"};
constexpr auto MAPS_DIRECTORY{"/Assets/Maps/"};
constexpr auto FONTS_DIRECTORY{"/Assets/Fonts/"};
constexpr auto SOUNDS_DIRECTORY{"/Assets/Sounds/"};
#endif
}  // namespace

namespace Paths
{

/// @brief Returns the path of the application executable based on OS.
/// @return Path to executable root directory
inline std::filesystem::path RootPath()
{
#ifdef WIN32
    wchar_t szPath[MAX_PATH];
    GetModuleFileNameW(NULL, szPath, MAX_PATH);
#else
    char szPath[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", szPath, PATH_MAX);
    if (count < 0 || count >= PATH_MAX) return {};  // some error
    szPath[count] = '\0';
#endif

    auto root_path = std::filesystem::path(szPath).parent_path();
    return root_path;
}

inline std::string SpritesDirectoryPath()
{
    return RootPath().string() + SPRITES_DIRECTORY;
}

inline std::string FontsDirectoryPath()
{
    return RootPath().string() + FONTS_DIRECTORY;
}

inline std::string SoundsDirectoryPath()
{
    return RootPath().string() + SOUNDS_DIRECTORY;
}

inline std::string MapsDirectoryPath()
{
    return RootPath().string() + MAPS_DIRECTORY;
}

}  // namespace Paths

#endif  // BLOCKJUMP_PATHS_H
