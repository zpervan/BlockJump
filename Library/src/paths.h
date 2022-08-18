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
#ifdef _WIN32
static constexpr auto Assets_Directory{"\\Assets\\sprites\\"};
#elif __linux__
static constexpr auto Assets_Directory{"/Assets/sprites/"};
#endif
}

namespace Paths
{

/// @brief Returns the path of the application executable based on OS.
/// @return Path to executable root directory
std::filesystem::path RootPath()
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
    spdlog::debug("Root path: {}", root_path.string());

    return root_path;
}

std::string AssetsPath()
{
    const auto assets_path = RootPath().string() + Assets_Directory;
    spdlog::debug("Assets path: {}", assets_path);
    return assets_path;
}

}  // namespace Paths

#endif  // BLOCKJUMP_PATHS_H
