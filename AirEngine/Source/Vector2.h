#pragma once

#include <type_traits>

constexpr float kPi = 3.1415926535897932384626f;

template<class Type>
class Vector2
{
	// Numbers only
	static_assert(std::is_integral_v<Type> || std::is_floating_point_v<Type>);

public:
	Type x;
	Type y;

	Vector2()
		: x(0)
		, y(0)
	{
	}

	Vector2(Type x, Type y)
		: x(x)
		, y(y)
	{
	}

	Vector2 operator*(const Type& other)
	{
		return Vector2(x * other, y * other);
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	float Magnitude()
	{
		return sqrtf((x * x) + (y * y));
	}

	Vector2<float> Normalized()
	{
		Vector2<float> vec;
		float mag = Magnitude();

		vec.x = x / mag;
		vec.y = y / mag;

		return vec;
	}
};
