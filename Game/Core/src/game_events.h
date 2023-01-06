#ifndef BLOCKJUMP_GAME_EVENTS_H
#define BLOCKJUMP_GAME_EVENTS_H

enum class GameEvents
{
    None = 0,
    Start,
    OnlineGame,
    Options,
    Quit,
    Menu
};

class GameEventSystem
{
  public:
    GameEvents& Poll();
    void Set(GameEvents event_type);

  private:
    GameEvents event_;
};

#endif  // BLOCKJUMP_GAME_EVENTS_H
