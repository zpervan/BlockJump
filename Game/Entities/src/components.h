#ifndef BLOCKJUMP_COMPONENTS_H
#define BLOCKJUMP_COMPONENTS_H

namespace Component
{

class Base
{
};

class Position : Base
{
  public:
    float x;
    float y;
};

class Velocity : Base
{
  public:
    float x;
    float y;
};

class State : Base
{
  public:
    enum class Entity
    {
        Idle = 0,
        Moving,
        Jumping,
        Dying
    };
};

class Collidable : Base
{
};

}  // namespace Component

#endif  // BLOCKJUMP_COMPONENTS_H
