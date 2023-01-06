#include "game_events.h"

#include <spdlog/spdlog.h>

#include <map>

namespace
{
std::map<GameEvents, std::string> map_game_events{{GameEvents::None, "None"},
                                                  {GameEvents::Start, "Start"},
                                                  {GameEvents::OnlineGame, "OnlineGame"},
                                                  {GameEvents::Options, "Options"},
                                                  {GameEvents::Quit, "Quit"},
                                                  {GameEvents::Menu, "Menu"}};
}

GameEvents& GameEventSystem::Poll()
{
    return event_;
}

void GameEventSystem::Set(GameEvents event_type)
{
    spdlog::debug("Setting to event type {}", map_game_events[event_type]);
    event_ = event_type;
}
