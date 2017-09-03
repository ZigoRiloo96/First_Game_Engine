#pragma once

enum class Direction
{
    from_Up,
    from_Down,
    from_Right,
    from_Left
};

struct Position
{
    int x;
    int y;
};

struct Frame
{
        Position position;
        int width;
        int height;
};