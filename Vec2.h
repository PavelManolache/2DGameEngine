#pragma once
#include <SFML/System/Vector2.hpp>

class Vec2
{
	
public:
	float x = 0;
	float y = 0;

	

	Vec2(float xin, float yin);

	Vec2 operator + (const Vec2& rhs) const;

	Vec2 operator - (const Vec2& rhs) const;

	Vec2 operator*(float scalar) const;
	

	sf::Vector2f toSFML() const;
};

