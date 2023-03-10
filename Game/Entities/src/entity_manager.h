#ifndef BLOCKJUMP_ENTITY_MANAGER_H
#define BLOCKJUMP_ENTITY_MANAGER_H

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <any>
#include <unordered_map>
#include <vector>

#include "Game/Entities/src/components.h"

using EntityId = int;

/// @TODO: Currently, the entities are stored in the map manager once deserialized - think of a way to directly store the data into the @c entity_manager
/// @TODO: Replace the raw pointers with smart_ptr to avoid memory leaks and dangling pointers
struct EntityData
{
    sf::RectangleShape shape;
    std::unordered_map<std::string, Component::Base*> components;
};

class EntityManager
{
  public:
    /// @brief Creates a new entity based with an generated Id based on the passed rectangle shape.
    /// @param shape Entity data
    void CreateEntity(const sf::RectangleShape& shape);

    /// @brief Adds new components to the entity with the specified Id.
    /// @param id Entity which should have the component
    /// @param component Component which will be added to the entity
    void AddComponent(EntityId id, Component::Base* component);

    /// @brief Clears all entities in the repository.
    void Purge();

    /// @brief Get the entity's component.
    /// @tparam T Component type
    /// @param id Entity Id
    /// @return Entity's component
    /// @example
    /// @code
    /// auto position = GetComponent<Position>(entity_id);
    /// auto velocity = GetComponent<Velocity>(entity_id);
    /// @endcode
    template <typename T>
    T* GetComponent(EntityId id)
    {
        auto& entity_component = entities_.at(id)->components;
        auto component_it = entity_component.find(typeid(T).name());

        if (component_it != entity_component.end())
        {
            return std::any_cast<T>(entity_component[typeid(T).name()]);
        }

        return nullptr;
    }

    /// @brief Get all entities with given component.
    /// @tparam T Component type
    /// @return All entities which have the given component
    /// @example
    /// @code
    /// auto entities_with_position = GetEntitiesWithComponent<Position>();
    /// @endcode
    template <typename T>
    std::vector<EntityData*> GetEntitiesWithComponent()
    {
        std::vector<EntityData*> entities_with_component;

        for (const auto& entity : entities_)
        {
            if (entity.second->components.count(typeid(T).name()))
            {
                entities_with_component.emplace_back(entity.second);
            }
        }

        return entities_with_component;
    }

    /** Getters and setters **/
    EntityData& GetEntity(EntityId id);
    std::unordered_map<EntityId, EntityData*>& GetEntities();

  private:
    std::unordered_map<EntityId, EntityData*> entities_;
    EntityId next_entity_id_{0};
};

#endif  // BLOCKJUMP_ENTITY_MANAGER_H
