#include "colorutil.hpp"

bool operator==(const Color &lhs, const Color &rhs)
{
    return lhs.r == rhs.r &&
           lhs.g == rhs.g &&
           lhs.b == rhs.b &&
           lhs.a == rhs.a;
}

Color operator*(const Color &lhs, const float rhs)
{
    return {
        static_cast<unsigned char>(lhs.r * rhs),
        static_cast<unsigned char>(lhs.g * rhs),
        static_cast<unsigned char>(lhs.b * rhs),
        static_cast<unsigned char>(lhs.a)};
};

std::size_t ColorHash::operator()(const Color &c) const
{
    return (static_cast<std::size_t>(c.r) << 24) |
           (static_cast<std::size_t>(c.g) << 16) |
           (static_cast<std::size_t>(c.b) << 8) |
           (static_cast<std::size_t>(c.a));
}