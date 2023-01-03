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
constexpr auto Sprites_Directory{"\\Assets\\Sprites\\"};
constexpr auto Fonts_Directory{"\\Assets\\Fonts\\"};
#else
constexpr auto Sprites_Directory{"/Assets/Sprites/"};
constexpr auto Fonts_Directory{"/Assets/Fonts/"};
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
    return RootPath().string() + Sprites_Directory;
}

inline std::string FontsDirectoryPath()
{
    return RootPath().string() + Fonts_Directory;
}

}  // namespace Paths

#endif  // BLOCKJUMP_PATHS_H
