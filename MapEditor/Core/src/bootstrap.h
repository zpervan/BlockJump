#ifndef BLOCKJUMP_BOOTSTRAP_H
#define BLOCKJUMP_BOOTSTRAP_H

#include <imgui.h>

class Bootstrap
{
  public:
    /// @brief Initialize all configuration parameters for the application.
    static void Initialize();

  private:
    static ImVec2 ScreenSize();
};

#endif  // BLOCKJUMP_BOOTSTRAP_H
