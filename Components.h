#pragma once
#include <SFML/Graphics.hpp>
#include "Vec2.h"

class CShape
{
public: 

	sf::CircleShape circle;

	CShape(float radius, int points, const sf::Color& fill, const sf::Color  outline, float thickness)
		: circle(radius, points)
	{

		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin({radius, radius });

	};
	
};

class CTransform
{
public:
	Vec2 pos = { 0.0 , 0.0 };
	Vec2 velocity = { 0.0 , 0.0 };
	float angle = 0;

	CTransform(const Vec2& p, const Vec2& v, float a)
		:pos(p), velocity(v), angle(a) {};
};

class CInput
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shoot = false;

	CInput(){}

};