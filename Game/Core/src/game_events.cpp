#include "game_events.h"

GameEvents& GameEventSystem::Poll()
{
    return event_;
}

void GameEventSystem::Set(GameEvents event_type)
{
    event_ = event_type;
}
