#pragma once
#include <raylib.h>
#include <cstddef>

bool operator==(const Color& lhs, const Color& rhs);
Color operator*(const Color& lhs, const float rhs);

struct ColorHash
{
    std::size_t operator()(const Color &c) const;
};