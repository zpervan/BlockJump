#ifndef BLOCKJUMP_PATHS_H
#define BLOCKJUMP_PATHS_H

#include <filesystem>
#include <string>
#include <spdlog/spdlog.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <linux/limits.h>
#endif

namespace
{
#ifdef WIN32
static constexpr auto Sprites_Directory{"\\Assets\\Sprites\\"};
#else
static constexpr auto Sprites_Directory{"/Assets/Sprites/"};
#endif
}

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

    const auto root_path = std::filesystem::path(szPath).parent_path();

    return root_path;
}

inline std::string SpritesDirectoryPath()
{
    return RootPath().string() + Sprites_Directory;
}

}  // namespace Paths

#endif  // BLOCKJUMP_PATHS_H
