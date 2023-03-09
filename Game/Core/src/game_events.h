#ifndef BLOCKJUMP_GAME_EVENTS_H
#define BLOCKJUMP_GAME_EVENTS_H

enum class GameEvents
{
    None = 0,
    GameMenu,
    GameLoad,
    GameRun,
    OnlineGameMenu,
    OnlineGameLoad,
    OnlineGameRun,
    Options,
    Quit,
    Menu
};

/// @brief Contains all custom game events.
/// @TODO: Consider to add SFML events so we have a single place for event management
class GameEventSystem
{
  public:
    GameEvents& Poll();
    void Set(GameEvents event_type);

  private:
    GameEvents event_;
};

#endif  // BLOCKJUMP_GAME_EVENTS_H
