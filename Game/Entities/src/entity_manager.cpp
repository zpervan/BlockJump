#include "entity_manager.h"

EntityId EntityManager::CreateEntity(const sf::RectangleShape& shape)
{
    ++entity_id_;

    auto entity_data = new EntityData;
    entity_data->shape = shape;

    entities_[entity_id_] = entity_data;
    return entity_id_;
}

void EntityManager::Purge()
{
    entities_.clear();
    entity_id_ = 0;
}

EntityData& EntityManager::GetEntity(EntityId id)
{
    return *entities_[id];
}

std::unordered_map<EntityId, EntityData*>& EntityManager::GetEntities()
{
    return entities_;
}
