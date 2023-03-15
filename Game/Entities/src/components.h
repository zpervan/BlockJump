#ifndef BLOCKJUMP_COMPONENTS_H
#define BLOCKJUMP_COMPONENTS_H

namespace Component
{

struct Base
{
};

struct Position : public Base
{
    float x;
    float y;
};

struct Velocity : public Base
{
    float x;
    float y;
};

struct State : public Base
{
    enum class Entity
    {
        Idle = 0,
        Moving,
        Jumping,
        Dying
    };
};

struct Collidable : public Base
{
    bool x_collision{false};
    bool y_collision{false};
};

}  // namespace Component

#endif  // BLOCKJUMP_COMPONENTS_H
