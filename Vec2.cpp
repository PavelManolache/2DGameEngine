#include "Vec2.h"

Vec2::Vec2(float xin , float yin)
	:x(xin) , y(yin)
{ }

Vec2 Vec2::operator +(const Vec2 & rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}
Vec2 Vec2::operator -(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(float scalar) const
{
	return Vec2(x * scalar, y * scalar);
}

sf::Vector2f Vec2::toSFML() const {
	return sf::Vector2f(x, y);
};

