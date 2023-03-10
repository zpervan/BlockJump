#ifndef BLOCKJUMP_COMPONENTS_H
#define BLOCKJUMP_COMPONENTS_H

namespace Component
{

struct Base
{
};

struct Position : Base
{
    float x;
    float y;
};

struct Velocity : Base
{
    float x;
    float y;
};

}  // namespace Component

#endif  // BLOCKJUMP_COMPONENTS_H
