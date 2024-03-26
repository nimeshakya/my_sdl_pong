#pragma once
#include <SDL.h>
class Vector2
{
public:
	Vector2() : e{ 0, 0 } {}
	Vector2(double a = 0, double b = 0) : e{ a, b } {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }

	// vector addition
	Vector2& operator+=(const Vector2& v)
	{
		e[0] += v.x();
		e[1] += v.y();
		return *this;
	}

	// vector multiplication (scalar)
	Vector2& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		return *this;
	}
private:
	double e[2];
};

/* Utility Functions */
inline Vector2 operator+(const Vector2& u, const Vector2& v)
{
	return Vector2(u.x() + v.x(), u.y() + v.y());
}

inline Vector2 operator-(const Vector2& u, const Vector2& v)
{
	return Vector2(u.x() - v.x(), u.y() - v.y());
}

inline Vector2 operator*(const Vector2& u, const Vector2& v)
{
	return Vector2(u.x() * v.x(), u.y() * v.y());
}

inline Vector2 operator*(double t, const Vector2& v)
{
	return Vector2(v.x() * t, v.y() * t);
}

inline Vector2 operator*(const Vector2& v, double t)
{
	return t * v;
}

inline Vector2 operator/(const Vector2& v, double t)
{
	return (1 / t) * v;
}