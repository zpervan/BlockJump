#include "map_editor_events.h"

#include <spdlog/spdlog.h>

#include <map>
#include <string>

namespace
{
static std::map<MapEditorEvent, std::string> mapped_map_editor_events{
    {MapEditorEvent::None, "None"},
    {MapEditorEvent::Add, "Add"},
    {MapEditorEvent::Delete, "Delete"},
    {MapEditorEvent::Edit, "Edit"},
};
}

void MapEditorEventSystem::Set(MapEditorEvent event_type)
{
    spdlog::debug("Setting map editor event of type {}", mapped_map_editor_events[event_type]);
    event_ = event_type;
}

MapEditorEvent& MapEditorEventSystem::Poll()
{
    return event_;
}
