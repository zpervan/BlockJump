#ifndef BLOCKJUMP_COMPONENTS_H
#define BLOCKJUMP_COMPONENTS_H

namespace Component
{

struct Base
{
    virtual ~Base() = default;
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
    bool x_left_collision{false};
    bool x_right_collision{false};
    bool y_top_collision{false};
    bool y_bottom_collision{false};

    void Reset()
    {
        x_left_collision = false;
        x_right_collision = false;
        y_top_collision = false;
        y_bottom_collision = false;
    }
};

}  // namespace Component

#endif  // BLOCKJUMP_COMPONENTS_H
