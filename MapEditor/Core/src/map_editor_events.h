#ifndef BLOCKJUMP_MAP_EDITOR_EVENTS_H
#define BLOCKJUMP_MAP_EDITOR_EVENTS_H

enum class MapEditorEvent
{
    None = 0,
    Add,
    Set,
    Edit,
    Delete,
    Saving,
    SavingConfirmed,
    Loading,
    LoadingConfirmed
};

class MapEditorEventSystem
{
  public:
    MapEditorEvent& Poll();
    void Set(MapEditorEvent event_type);

  private:
    MapEditorEvent event_;
};

#endif  // BLOCKJUMP_MAP_EDITOR_EVENTS_H
